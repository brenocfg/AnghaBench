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
 unsigned long UINT_MAX ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 unsigned long page_size ; 
 unsigned long perf_event_mlock_kb_in_pages () ; 

size_t evlist__mmap_size(unsigned long pages)
{
	if (pages == UINT_MAX)
		pages = perf_event_mlock_kb_in_pages();
	else if (!is_power_of_2(pages))
		return 0;

	return (pages + 1) * page_size;
}