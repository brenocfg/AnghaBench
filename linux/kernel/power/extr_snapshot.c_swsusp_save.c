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
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  copy_bm ; 
 int /*<<< orphan*/  copy_data_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int count_data_pages () ; 
 unsigned int count_highmem_pages () ; 
 int /*<<< orphan*/  drain_local_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enough_free_mem (unsigned int,unsigned int) ; 
 unsigned int nr_copy_pages ; 
 int /*<<< orphan*/  nr_meta_pages ; 
 int /*<<< orphan*/  orig_bm ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 scalar_t__ swsusp_alloc (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

int swsusp_save(void)
{
	unsigned int nr_pages, nr_highmem;

	pr_info("Creating hibernation image:\n");

	drain_local_pages(NULL);
	nr_pages = count_data_pages();
	nr_highmem = count_highmem_pages();
	pr_info("Need to copy %u pages\n", nr_pages + nr_highmem);

	if (!enough_free_mem(nr_pages, nr_highmem)) {
		pr_err("Not enough free memory\n");
		return -ENOMEM;
	}

	if (swsusp_alloc(&copy_bm, nr_pages, nr_highmem)) {
		pr_err("Memory allocation failed\n");
		return -ENOMEM;
	}

	/*
	 * During allocating of suspend pagedir, new cold pages may appear.
	 * Kill them.
	 */
	drain_local_pages(NULL);
	copy_data_pages(&copy_bm, &orig_bm);

	/*
	 * End of critical section. From now on, we can write to memory,
	 * but we should not touch disk. This specially means we must _not_
	 * touch swap space! Except we must write out our image of course.
	 */

	nr_pages += nr_highmem;
	nr_copy_pages = nr_pages;
	nr_meta_pages = DIV_ROUND_UP(nr_pages * sizeof(long), PAGE_SIZE);

	pr_info("Hibernation image created (%d pages copied)\n", nr_pages);

	return 0;
}