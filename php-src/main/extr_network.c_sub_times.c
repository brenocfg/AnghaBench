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
struct timeval {long tv_usec; long tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static inline void sub_times(struct timeval a, struct timeval b, struct timeval *result)
{
	result->tv_usec = a.tv_usec - b.tv_usec;
	if (result->tv_usec < 0L) {
		a.tv_sec--;
		result->tv_usec += 1000000L;
	}
	result->tv_sec = a.tv_sec - b.tv_sec;
	if (result->tv_sec < 0L) {
		result->tv_sec++;
		result->tv_usec -= 1000000L;
	}
}