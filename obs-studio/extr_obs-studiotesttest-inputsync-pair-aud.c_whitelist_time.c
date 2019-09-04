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
typedef  int uint64_t ;

/* Variables and functions */
 int starting_time ; 

__attribute__((used)) static inline bool whitelist_time(uint64_t ts, uint64_t interval,
		uint64_t fps_num, uint64_t fps_den)
{
	if (!starting_time)
		return false;

	uint64_t count = (ts - starting_time) / interval;
	uint64_t sec = count * fps_den / fps_num;
	return sec % 2 == 1;
}