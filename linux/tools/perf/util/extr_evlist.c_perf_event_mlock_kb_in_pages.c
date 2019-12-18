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
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 int page_size ; 
 unsigned long rounddown_pow_of_two (unsigned long) ; 
 scalar_t__ sysctl__read_int (char*,int*) ; 

unsigned long perf_event_mlock_kb_in_pages(void)
{
	unsigned long pages;
	int max;

	if (sysctl__read_int("kernel/perf_event_mlock_kb", &max) < 0) {
		/*
		 * Pick a once upon a time good value, i.e. things look
		 * strange since we can't read a sysctl value, but lets not
		 * die yet...
		 */
		max = 512;
	} else {
		max -= (page_size / 1024);
	}

	pages = (max * 1024) / page_size;
	if (!is_power_of_2(pages))
		pages = rounddown_pow_of_two(pages);

	return pages;
}