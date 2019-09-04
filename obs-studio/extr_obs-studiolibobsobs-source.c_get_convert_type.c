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
typedef  enum convert_type { ____Placeholder_convert_type } convert_type ;

/* Variables and functions */
 int CONVERT_420 ; 
 int CONVERT_422_U ; 
 int CONVERT_422_Y ; 
 int CONVERT_444 ; 
 int CONVERT_800 ; 
 int CONVERT_NONE ; 
 int CONVERT_NV12 ; 
 int CONVERT_RGB_LIMITED ; 
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

__attribute__((used)) static inline enum convert_type get_convert_type(enum video_format format,
		bool full_range)
{
	switch (format) {
	case VIDEO_FORMAT_I420:
		return CONVERT_420;
	case VIDEO_FORMAT_NV12:
		return CONVERT_NV12;
	case VIDEO_FORMAT_I444:
		return CONVERT_444;

	case VIDEO_FORMAT_YVYU:
	case VIDEO_FORMAT_YUY2:
		return CONVERT_422_Y;
	case VIDEO_FORMAT_UYVY:
		return CONVERT_422_U;

	case VIDEO_FORMAT_Y800:
		return CONVERT_800;

	case VIDEO_FORMAT_NONE:
	case VIDEO_FORMAT_RGBA:
	case VIDEO_FORMAT_BGRA:
	case VIDEO_FORMAT_BGRX:
		return full_range ? CONVERT_NONE : CONVERT_RGB_LIMITED;
	}

	return CONVERT_NONE;
}