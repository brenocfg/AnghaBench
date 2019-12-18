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
typedef  enum video_range_type { ____Placeholder_video_range_type } video_range_type ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
 int VIDEO_RANGE_DEFAULT ; 
 int VIDEO_RANGE_FULL ; 
 int VIDEO_RANGE_PARTIAL ; 
 scalar_t__ format_is_yuv (int) ; 

__attribute__((used)) static inline enum video_range_type
resolve_video_range(enum video_format format, enum video_range_type range)
{
	if (range == VIDEO_RANGE_DEFAULT) {
		range = format_is_yuv(format) ? VIDEO_RANGE_PARTIAL
					      : VIDEO_RANGE_FULL;
	}

	return range;
}