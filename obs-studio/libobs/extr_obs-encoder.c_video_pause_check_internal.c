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
typedef  scalar_t__ uint64_t ;
struct pause_data {scalar_t__ ts_start; scalar_t__ ts_end; scalar_t__ last_video_ts; } ;

/* Variables and functions */

__attribute__((used)) static inline bool video_pause_check_internal(struct pause_data *pause,
					      uint64_t ts)
{
	pause->last_video_ts = ts;
	if (!pause->ts_start) {
		return false;
	}

	if (ts == pause->ts_end) {
		pause->ts_start = 0;
		pause->ts_end = 0;

	} else if (ts >= pause->ts_start) {
		return true;
	}

	return false;
}