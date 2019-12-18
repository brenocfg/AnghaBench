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
struct pause_data {scalar_t__ ts_start; scalar_t__ ts_end; int /*<<< orphan*/  ts_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline void end_pause(struct pause_data *pause, uint64_t ts)
{
	if (!pause->ts_end) {
		pause->ts_end = ts;
		pause->ts_offset += pause->ts_end - pause->ts_start;
	}
}