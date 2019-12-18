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
struct timespec {int dummy; } ;

/* Variables and functions */
 long long ts_to_nsec (struct timespec) ; 

long long diff_timespec(struct timespec start, struct timespec end)
{
	long long start_ns, end_ns;

	start_ns = ts_to_nsec(start);
	end_ns = ts_to_nsec(end);
	return end_ns - start_ns;
}