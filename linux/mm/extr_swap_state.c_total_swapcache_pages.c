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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {int dummy; } ;
struct address_space {scalar_t__ nrpages; } ;

/* Variables and functions */
 unsigned int MAX_SWAPFILES ; 
 struct swap_info_struct* get_swap_device (int /*<<< orphan*/ ) ; 
 unsigned int* nr_swapper_spaces ; 
 int /*<<< orphan*/  put_swap_device (struct swap_info_struct*) ; 
 struct address_space** swapper_spaces ; 
 int /*<<< orphan*/  swp_entry (unsigned int,int) ; 
 int /*<<< orphan*/  swp_swap_info (int /*<<< orphan*/ ) ; 

unsigned long total_swapcache_pages(void)
{
	unsigned int i, j, nr;
	unsigned long ret = 0;
	struct address_space *spaces;
	struct swap_info_struct *si;

	for (i = 0; i < MAX_SWAPFILES; i++) {
		swp_entry_t entry = swp_entry(i, 1);

		/* Avoid get_swap_device() to warn for bad swap entry */
		if (!swp_swap_info(entry))
			continue;
		/* Prevent swapoff to free swapper_spaces */
		si = get_swap_device(entry);
		if (!si)
			continue;
		nr = nr_swapper_spaces[i];
		spaces = swapper_spaces[i];
		for (j = 0; j < nr; j++)
			ret += spaces[j].nrpages;
		put_swap_device(si);
	}
	return ret;
}