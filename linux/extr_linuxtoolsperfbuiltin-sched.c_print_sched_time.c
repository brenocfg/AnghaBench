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

/* Variables and functions */
 unsigned long long NSEC_PER_MSEC ; 
 unsigned long long NSEC_PER_USEC ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long,unsigned long) ; 

__attribute__((used)) static inline void print_sched_time(unsigned long long nsecs, int width)
{
	unsigned long msecs;
	unsigned long usecs;

	msecs  = nsecs / NSEC_PER_MSEC;
	nsecs -= msecs * NSEC_PER_MSEC;
	usecs  = nsecs / NSEC_PER_USEC;
	printf("%*lu.%03lu ", width, msecs, usecs);
}