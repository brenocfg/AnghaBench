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
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int GS_BGRA ; 
 int GS_BGRX ; 
 int GS_RGBA ; 
#define  VIDEO_FORMAT_AYUV 133 
#define  VIDEO_FORMAT_BGRA 132 
#define  VIDEO_FORMAT_I40A 131 
#define  VIDEO_FORMAT_I42A 130 
#define  VIDEO_FORMAT_RGBA 129 
#define  VIDEO_FORMAT_YUVA 128 

__attribute__((used)) static inline enum gs_color_format
convert_video_format(enum video_format format)
{
	switch (format) {
	case VIDEO_FORMAT_RGBA:
		return GS_RGBA;
	case VIDEO_FORMAT_BGRA:
	case VIDEO_FORMAT_I40A:
	case VIDEO_FORMAT_I42A:
	case VIDEO_FORMAT_YUVA:
	case VIDEO_FORMAT_AYUV:
		return GS_BGRA;
	default:
		return GS_BGRX;
	}
}