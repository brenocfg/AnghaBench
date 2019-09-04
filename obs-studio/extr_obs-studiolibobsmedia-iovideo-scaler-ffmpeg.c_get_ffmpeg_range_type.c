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

/* Variables and functions */
#define  VIDEO_RANGE_DEFAULT 130 
#define  VIDEO_RANGE_FULL 129 
#define  VIDEO_RANGE_PARTIAL 128 

__attribute__((used)) static inline int get_ffmpeg_range_type(enum video_range_type type)
{
	switch (type) {
	case VIDEO_RANGE_DEFAULT: return 0;
	case VIDEO_RANGE_PARTIAL: return 0;
	case VIDEO_RANGE_FULL:    return 1;
	}

	return 0;
}