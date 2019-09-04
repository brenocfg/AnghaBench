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
typedef  enum video_scale_type { ____Placeholder_video_scale_type } video_scale_type ;

/* Variables and functions */
 int SWS_AREA ; 
 int SWS_BICUBIC ; 
 int SWS_BILINEAR ; 
 int SWS_FAST_BILINEAR ; 
 int SWS_POINT ; 
#define  VIDEO_SCALE_BICUBIC 132 
#define  VIDEO_SCALE_BILINEAR 131 
#define  VIDEO_SCALE_DEFAULT 130 
#define  VIDEO_SCALE_FAST_BILINEAR 129 
#define  VIDEO_SCALE_POINT 128 

__attribute__((used)) static inline int get_ffmpeg_scale_type(enum video_scale_type type)
{
	switch (type) {
	case VIDEO_SCALE_DEFAULT:       return SWS_FAST_BILINEAR;
	case VIDEO_SCALE_POINT:         return SWS_POINT;
	case VIDEO_SCALE_FAST_BILINEAR: return SWS_FAST_BILINEAR;
	case VIDEO_SCALE_BILINEAR:      return SWS_BILINEAR | SWS_AREA;
	case VIDEO_SCALE_BICUBIC:       return SWS_BICUBIC;
	}

	return SWS_POINT;
}