#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum gs_sample_filter { ____Placeholder_gs_sample_filter } gs_sample_filter ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_LINEAR_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  GL_LINEAR_MIPMAP_NEAREST ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_NEAREST_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST_MIPMAP_NEAREST ; 
#define  GS_FILTER_ANISOTROPIC 136 
#define  GS_FILTER_LINEAR 135 
#define  GS_FILTER_MIN_LINEAR_MAG_MIP_POINT 134 
#define  GS_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR 133 
#define  GS_FILTER_MIN_MAG_LINEAR_MIP_POINT 132 
#define  GS_FILTER_MIN_MAG_POINT_MIP_LINEAR 131 
#define  GS_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT 130 
#define  GS_FILTER_MIN_POINT_MAG_MIP_LINEAR 129 
#define  GS_FILTER_POINT 128 

__attribute__((used)) static inline void convert_filter(enum gs_sample_filter filter,
		GLint *min_filter, GLint *mag_filter)
{
	switch (filter) {
	case GS_FILTER_POINT:
		*min_filter = GL_NEAREST_MIPMAP_NEAREST;
		*mag_filter = GL_NEAREST;
		return;
	case GS_FILTER_LINEAR:
		*min_filter = GL_LINEAR_MIPMAP_LINEAR;
		*mag_filter = GL_LINEAR;
		return;
	case GS_FILTER_MIN_MAG_POINT_MIP_LINEAR:
		*min_filter = GL_NEAREST_MIPMAP_LINEAR;
		*mag_filter = GL_NEAREST;
		return;
	case GS_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
		*min_filter = GL_NEAREST_MIPMAP_NEAREST;
		*mag_filter = GL_LINEAR;
		return;
	case GS_FILTER_MIN_POINT_MAG_MIP_LINEAR:
		*min_filter = GL_NEAREST_MIPMAP_LINEAR;
		*mag_filter = GL_LINEAR;
		return;
	case GS_FILTER_MIN_LINEAR_MAG_MIP_POINT:
		*min_filter = GL_LINEAR_MIPMAP_NEAREST;
		*mag_filter = GL_NEAREST;
		return;
	case GS_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
		*min_filter = GL_LINEAR_MIPMAP_LINEAR;
		*mag_filter = GL_NEAREST;
		return;
	case GS_FILTER_MIN_MAG_LINEAR_MIP_POINT:
		*min_filter = GL_LINEAR_MIPMAP_NEAREST;
		*mag_filter = GL_LINEAR;
		return;
	case GS_FILTER_ANISOTROPIC:
		*min_filter = GL_LINEAR_MIPMAP_LINEAR;
		*mag_filter = GL_LINEAR;
		return;
	}

	*min_filter = GL_NEAREST_MIPMAP_NEAREST;
	*mag_filter = GL_NEAREST;
}