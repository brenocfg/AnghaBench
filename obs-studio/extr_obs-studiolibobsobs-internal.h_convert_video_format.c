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
 int VIDEO_FORMAT_BGRA ; 
 int VIDEO_FORMAT_RGBA ; 

__attribute__((used)) static inline enum gs_color_format convert_video_format(
		enum video_format format)
{
	if (format == VIDEO_FORMAT_RGBA)
		return GS_RGBA;
	else if (format == VIDEO_FORMAT_BGRA)
		return GS_BGRA;

	return GS_BGRX;
}