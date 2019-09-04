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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_BGRA ; 
 int AV_PIX_FMT_GRAY8 ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_NV12 ; 
 int AV_PIX_FMT_RGBA ; 
 int AV_PIX_FMT_UYVY422 ; 
 int AV_PIX_FMT_YUV420P ; 
 int AV_PIX_FMT_YUV444P ; 
 int AV_PIX_FMT_YUYV422 ; 
#define  VIDEO_FORMAT_BGRA 138 
#define  VIDEO_FORMAT_BGRX 137 
#define  VIDEO_FORMAT_I420 136 
#define  VIDEO_FORMAT_I444 135 
#define  VIDEO_FORMAT_NONE 134 
#define  VIDEO_FORMAT_NV12 133 
#define  VIDEO_FORMAT_RGBA 132 
#define  VIDEO_FORMAT_UYVY 131 
#define  VIDEO_FORMAT_Y800 130 
#define  VIDEO_FORMAT_YUY2 129 
#define  VIDEO_FORMAT_YVYU 128 

__attribute__((used)) static inline enum AVPixelFormat obs_to_ffmpeg_video_format(
		enum video_format format)
{
	switch (format) {
	case VIDEO_FORMAT_NONE: return AV_PIX_FMT_NONE;
	case VIDEO_FORMAT_I444: return AV_PIX_FMT_YUV444P;
	case VIDEO_FORMAT_I420: return AV_PIX_FMT_YUV420P;
	case VIDEO_FORMAT_NV12: return AV_PIX_FMT_NV12;
	case VIDEO_FORMAT_YVYU: return AV_PIX_FMT_NONE;
	case VIDEO_FORMAT_YUY2: return AV_PIX_FMT_YUYV422;
	case VIDEO_FORMAT_UYVY: return AV_PIX_FMT_UYVY422;
	case VIDEO_FORMAT_RGBA: return AV_PIX_FMT_RGBA;
	case VIDEO_FORMAT_BGRA: return AV_PIX_FMT_BGRA;
	case VIDEO_FORMAT_BGRX: return AV_PIX_FMT_BGRA;
	case VIDEO_FORMAT_Y800: return AV_PIX_FMT_GRAY8;
	}

	return AV_PIX_FMT_NONE;
}