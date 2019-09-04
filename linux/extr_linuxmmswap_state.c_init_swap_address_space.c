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
struct address_space {int /*<<< orphan*/ * a_ops; int /*<<< orphan*/  i_mmap_writable; int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SWAP_ADDRESS_SPACE_PAGES ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct address_space* kvcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_no_writeback_tags (struct address_space*) ; 
 unsigned int* nr_swapper_spaces ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct address_space*) ; 
 int /*<<< orphan*/  swap_aops ; 
 int /*<<< orphan*/ * swapper_spaces ; 

int init_swap_address_space(unsigned int type, unsigned long nr_pages)
{
	struct address_space *spaces, *space;
	unsigned int i, nr;

	nr = DIV_ROUND_UP(nr_pages, SWAP_ADDRESS_SPACE_PAGES);
	spaces = kvcalloc(nr, sizeof(struct address_space), GFP_KERNEL);
	if (!spaces)
		return -ENOMEM;
	for (i = 0; i < nr; i++) {
		space = spaces + i;
		INIT_RADIX_TREE(&space->i_pages, GFP_ATOMIC|__GFP_NOWARN);
		atomic_set(&space->i_mmap_writable, 0);
		space->a_ops = &swap_aops;
		/* swap cache doesn't use writeback related tags */
		mapping_set_no_writeback_tags(space);
	}
	nr_swapper_spaces[type] = nr;
	rcu_assign_pointer(swapper_spaces[type], spaces);

	return 0;
}