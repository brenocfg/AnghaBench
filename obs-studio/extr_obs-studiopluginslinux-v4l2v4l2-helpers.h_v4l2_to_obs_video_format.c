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
typedef  int uint_fast32_t ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
#define  V4L2_PIX_FMT_NV12 133 
#define  V4L2_PIX_FMT_UYVY 132 
#define  V4L2_PIX_FMT_YUV420 131 
#define  V4L2_PIX_FMT_YUYV 130 
#define  V4L2_PIX_FMT_YVU420 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int VIDEO_FORMAT_I420 ; 
 int VIDEO_FORMAT_NONE ; 
 int VIDEO_FORMAT_NV12 ; 
 int VIDEO_FORMAT_UYVY ; 
 int VIDEO_FORMAT_YUY2 ; 
 int VIDEO_FORMAT_YVYU ; 

__attribute__((used)) static inline enum video_format v4l2_to_obs_video_format(uint_fast32_t format)
{
	switch (format) {
	case V4L2_PIX_FMT_YVYU:   return VIDEO_FORMAT_YVYU;
	case V4L2_PIX_FMT_YUYV:   return VIDEO_FORMAT_YUY2;
	case V4L2_PIX_FMT_UYVY:   return VIDEO_FORMAT_UYVY;
	case V4L2_PIX_FMT_NV12:   return VIDEO_FORMAT_NV12;
	case V4L2_PIX_FMT_YUV420: return VIDEO_FORMAT_I420;
	case V4L2_PIX_FMT_YVU420: return VIDEO_FORMAT_I420;
#ifdef V4L2_PIX_FMT_XBGR32
	case V4L2_PIX_FMT_XBGR32: return VIDEO_FORMAT_BGRX;
#endif
#ifdef V4L2_PIX_FMT_ABGR32
	case V4L2_PIX_FMT_ABGR32: return VIDEO_FORMAT_BGRA;
#endif
	default:                  return VIDEO_FORMAT_NONE;
	}
}