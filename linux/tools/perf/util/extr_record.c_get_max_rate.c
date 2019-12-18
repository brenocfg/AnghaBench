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
 int sysctl__read_int (char*,int*) ; 

__attribute__((used)) static int get_max_rate(unsigned int *rate)
{
	return sysctl__read_int("kernel/perf_event_max_sample_rate", (int *)rate);
}