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
struct timespec {unsigned long tv_sec; unsigned long tv_nsec; } ;

/* Variables and functions */

__attribute__((used)) static inline void add_ms_to_ts(struct timespec *ts,
		unsigned long milliseconds)
{
	ts->tv_sec += milliseconds/1000;
	ts->tv_nsec += (milliseconds%1000)*1000000;
	if (ts->tv_nsec > 1000000000) {
		ts->tv_sec += 1;
		ts->tv_nsec -= 1000000000;
	}
}