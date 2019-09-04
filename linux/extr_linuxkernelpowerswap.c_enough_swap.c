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
 unsigned int PAGES_FOR_IO ; 
 unsigned int count_swap_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  root_swap ; 

__attribute__((used)) static int enough_swap(unsigned int nr_pages)
{
	unsigned int free_swap = count_swap_pages(root_swap, 1);
	unsigned int required;

	pr_debug("Free swap pages: %u\n", free_swap);

	required = PAGES_FOR_IO + nr_pages;
	return free_swap > required;
}