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
 int os_gettime_ns () ; 

__attribute__((used)) static inline bool frame_ready(uint64_t interval)
{
	static uint64_t last_time = 0;
	uint64_t elapsed;
	uint64_t t;

	if (!interval) {
		return true;
	}

	t = os_gettime_ns();
	elapsed = t - last_time;

	if (elapsed < interval) {
		return false;
	}

	last_time = (elapsed > interval * 2) ? t : last_time + interval;
	return true;
}