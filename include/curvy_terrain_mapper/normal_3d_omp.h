/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2010-2011, Willow Garage, Inc.
 *  Copyright (c) 2012-, Open Perception, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the copyright holder(s) nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 *
 */

#ifndef PCL_NORMAL_3D_OMP_H_
#define PCL_NORMAL_3D_OMP_H_

#include <pcl/features/normal_3d.h>

namespace pcl
{
  /** \brief NormalEstimationOMP estimates local surface properties at each 3D point, such as surface normals and
    * curvatures, in parallel, using the OpenMP standard.
    * \author Radu Bogdan Rusu
    * \ingroup features
    */
  template <typename PointInT, typename PointOutT>
  class NormalEstimationOMP: public NormalEstimation<PointInT, PointOutT>
  {
    public:
      typedef std::shared_ptr<NormalEstimationOMP<PointInT, PointOutT> > Ptr;
      typedef std::shared_ptr<const NormalEstimationOMP<PointInT, PointOutT> > ConstPtr;
      using NormalEstimation<PointInT, PointOutT>::feature_name_;
      using NormalEstimation<PointInT, PointOutT>::getClassName;
      using NormalEstimation<PointInT, PointOutT>::indices_;
      using NormalEstimation<PointInT, PointOutT>::input_;
      using NormalEstimation<PointInT, PointOutT>::k_;
      using NormalEstimation<PointInT, PointOutT>::vpx_;
      using NormalEstimation<PointInT, PointOutT>::vpy_;
      using NormalEstimation<PointInT, PointOutT>::vpz_;
      using NormalEstimation<PointInT, PointOutT>::search_parameter_;
      using NormalEstimation<PointInT, PointOutT>::surface_;
      using NormalEstimation<PointInT, PointOutT>::getViewPoint;

      typedef typename NormalEstimation<PointInT, PointOutT>::PointCloudOut PointCloudOut;

    public:
      /** \brief Initialize the scheduler and set the number of threads to use.
        * \param nr_threads the number of hardware threads to use (0 sets the value back to automatic)
        */
      NormalEstimationOMP (unsigned int nr_threads = 0) : threads_ (nr_threads)
      {
        feature_name_ = "NormalEstimationOMP";
      }

      bool gpActive;
      double gpAngle;

      bool fsActive;
      double fsAngle;
      double fsRange;

      bool pfActive;
      double pfAngleHigh;
      double pfAngleLow;

      std::vector<int> floorIndices;
      std::vector<int> ghostPointIndices;
      std::vector<int> normalFilterIndices;

      inline void getFloorIndices(std::vector<int>& output)
      {
    	  output = floorIndices;
      }

      inline void getGhostIndices(std::vector<int>& output)
      {
    	  output = ghostPointIndices;
      }

      inline void getNormalIndices(std::vector<int>& output)
      {
    	  output = normalFilterIndices;
      }

      inline void setGpActive(bool input)
      {
    	  gpActive = input;
      }
      inline void setGpAngle(double input)
      {
    	  gpAngle = input;
      }

      inline void setFsActive(bool input)
      {
    	  fsActive = input;
      }
      inline void setFsAngle(double input)
      {
    	  fsAngle = cos(input/180*M_PI);
      }
      inline void setFsRange(double input)
      {
    	  fsRange = input;
      }

      inline void setPfActive(bool input)
      {
    	  pfActive = input;
      }
      inline void setPfAngle(double input)
      {
    	  pfAngleHigh = cos(input/180*M_PI);
    	  pfAngleLow = cos((90-input)/180*M_PI);
      }

      /** \brief Initialize the scheduler and set the number of threads to use.
        * \param nr_threads the number of hardware threads to use (0 sets the value back to automatic)
        */
      inline void
      setNumberOfThreads (unsigned int nr_threads = 0) { threads_ = nr_threads; }

    protected:
      /** \brief The number of threads the scheduler should use. */
      unsigned int threads_;

    private:
      /** \brief Estimate normals for all points given in <setInputCloud (), setIndices ()> using the surface in
        * setSearchSurface () and the spatial locator in setSearchMethod ()
        * \param output the resultant point cloud model dataset that contains surface normals and curvatures
        */
      void
      computeFeature (PointCloudOut &output);

  };
}

//#ifdef PCL_NO_PRECOMPILE
#include <curvy_terrain_mapper/impl/normal_3d_omp.hpp>
//#endif

#endif  //#ifndef PCL_NORMAL_3D_OMP_H_
