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
 unsigned long SIZE_MAX ; 
 unsigned long UINT_MAX ; 
 unsigned long page_size ; 
 long parse_pages_arg (char const*,int,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int __perf_evlist__parse_mmap_pages(unsigned int *mmap_pages, const char *str)
{
	unsigned long max = UINT_MAX;
	long pages;

	if (max > SIZE_MAX / page_size)
		max = SIZE_MAX / page_size;

	pages = parse_pages_arg(str, 1, max);
	if (pages < 0) {
		pr_err("Invalid argument for --mmap_pages/-m\n");
		return -1;
	}

	*mmap_pages = pages;
	return 0;
}