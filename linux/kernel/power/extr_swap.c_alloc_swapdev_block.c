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
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_swap_page_of_type (int) ; 
 int /*<<< orphan*/  swap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapdev_block (int,unsigned long) ; 
 int /*<<< orphan*/  swp_entry (int,unsigned long) ; 
 unsigned long swp_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ swsusp_extents_insert (unsigned long) ; 

sector_t alloc_swapdev_block(int swap)
{
	unsigned long offset;

	offset = swp_offset(get_swap_page_of_type(swap));
	if (offset) {
		if (swsusp_extents_insert(offset))
			swap_free(swp_entry(swap, offset));
		else
			return swapdev_block(swap, offset);
	}
	return 0;
}