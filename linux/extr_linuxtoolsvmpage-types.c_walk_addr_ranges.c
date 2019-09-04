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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  add_addr_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checked_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpageflags_fd ; 
 int /*<<< orphan*/  mark_page_idle (int /*<<< orphan*/ ) ; 
 int nr_addr_ranges ; 
 int /*<<< orphan*/  opt_kpageflags ; 
 scalar_t__ opt_mark_idle ; 
 int /*<<< orphan*/ * opt_offset ; 
 int /*<<< orphan*/  opt_pid ; 
 int /*<<< orphan*/ * opt_size ; 
 int /*<<< orphan*/  walk_pfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void walk_addr_ranges(void)
{
	int i;

	kpageflags_fd = checked_open(opt_kpageflags, O_RDONLY);

	if (!nr_addr_ranges)
		add_addr_range(0, ULONG_MAX);

	for (i = 0; i < nr_addr_ranges; i++)
		if (!opt_pid)
			walk_pfn(opt_offset[i], opt_offset[i], opt_size[i], 0);
		else
			walk_task(opt_offset[i], opt_size[i]);

	if (opt_mark_idle)
		mark_page_idle(0);

	close(kpageflags_fd);
}