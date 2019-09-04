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
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
#define  AV_PIX_FMT_BGR0 136 
#define  AV_PIX_FMT_BGRA 135 
#define  AV_PIX_FMT_NONE 134 
#define  AV_PIX_FMT_NV12 133 
#define  AV_PIX_FMT_RGBA 132 
#define  AV_PIX_FMT_UYVY422 131 
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV444P 129 
#define  AV_PIX_FMT_YUYV422 128 
 int VIDEO_FORMAT_BGRA ; 
 int VIDEO_FORMAT_BGRX ; 
 int VIDEO_FORMAT_I420 ; 
 int VIDEO_FORMAT_I444 ; 
 int VIDEO_FORMAT_NONE ; 
 int VIDEO_FORMAT_NV12 ; 
 int VIDEO_FORMAT_RGBA ; 
 int VIDEO_FORMAT_UYVY ; 
 int VIDEO_FORMAT_YUY2 ; 

__attribute__((used)) static inline enum video_format convert_pixel_format(int f)
{
	switch (f) {
	case AV_PIX_FMT_NONE:    return VIDEO_FORMAT_NONE;
	case AV_PIX_FMT_YUV420P: return VIDEO_FORMAT_I420;
	case AV_PIX_FMT_NV12:    return VIDEO_FORMAT_NV12;
	case AV_PIX_FMT_YUYV422: return VIDEO_FORMAT_YUY2;
	case AV_PIX_FMT_YUV444P: return VIDEO_FORMAT_I444;
	case AV_PIX_FMT_UYVY422: return VIDEO_FORMAT_UYVY;
	case AV_PIX_FMT_RGBA:    return VIDEO_FORMAT_RGBA;
	case AV_PIX_FMT_BGRA:    return VIDEO_FORMAT_BGRA;
	case AV_PIX_FMT_BGR0:    return VIDEO_FORMAT_BGRX;
	default:;
	}

	return VIDEO_FORMAT_NONE;
}