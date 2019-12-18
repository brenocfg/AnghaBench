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
 int VIDEO_RANGE_FULL ; 
 int resolve_video_range (int,int) ; 

__attribute__((used)) static inline const char *get_video_range_name(enum video_format format,
					       enum video_range_type range)
{
	range = resolve_video_range(format, range);
	return range == VIDEO_RANGE_FULL ? "Full" : "Partial";
}