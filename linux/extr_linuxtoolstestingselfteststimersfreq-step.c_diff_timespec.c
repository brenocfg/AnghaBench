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
struct timespec {double tv_sec; int tv_nsec; } ;

/* Variables and functions */

__attribute__((used)) static double diff_timespec(struct timespec *ts1, struct timespec *ts2)
{
	return ts1->tv_sec - ts2->tv_sec + (ts1->tv_nsec - ts2->tv_nsec) / 1e9;
}