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

__attribute__((used)) static inline const char *get_video_format_name(enum video_format format)
{
	switch (format) {
	case VIDEO_FORMAT_I420: return "I420";
	case VIDEO_FORMAT_NV12: return "NV12";
	case VIDEO_FORMAT_YVYU: return "YVYU";
	case VIDEO_FORMAT_YUY2: return "YUY2";
	case VIDEO_FORMAT_UYVY: return "UYVY";
	case VIDEO_FORMAT_RGBA: return "RGBA";
	case VIDEO_FORMAT_BGRA: return "BGRA";
	case VIDEO_FORMAT_BGRX: return "BGRX";
	case VIDEO_FORMAT_I444: return "I444";
	case VIDEO_FORMAT_Y800: return "Y800";
	case VIDEO_FORMAT_NONE:;
	}

	return "None";
}