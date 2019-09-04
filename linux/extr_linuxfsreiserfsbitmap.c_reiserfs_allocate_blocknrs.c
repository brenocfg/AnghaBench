#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_8__ {scalar_t__ search_start; int /*<<< orphan*/  inode; TYPE_3__* th; scalar_t__ preallocate; int /*<<< orphan*/  formatted_node; } ;
typedef  TYPE_1__ reiserfs_blocknr_hint_t ;
typedef  int /*<<< orphan*/  b_blocknr_t ;
struct TYPE_10__ {int reserved_blocks; } ;
struct TYPE_9__ {struct super_block* t_super; } ;

/* Variables and functions */
 int CARRY_ON ; 
 int NO_DISK_SPACE ; 
 TYPE_7__* REISERFS_SB (struct super_block*) ; 
 scalar_t__ SB_BLOCK_COUNT (struct super_block*) ; 
 int SB_FREE_BLOCKS (struct super_block*) ; 
 int blocknrs_and_prealloc_arrays_from_search_start (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  determine_search_start (TYPE_1__*,int) ; 
 int /*<<< orphan*/  reiserfs_free_block (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int use_preallocated_list_if_available (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int reiserfs_allocate_blocknrs(reiserfs_blocknr_hint_t *hint,
			       b_blocknr_t *new_blocknrs,
			       int amount_needed,
			       /* Amount of blocks we have already reserved */
			       int reserved_by_us)
{
	int initial_amount_needed = amount_needed;
	int ret;
	struct super_block *s = hint->th->t_super;

	/* Check if there is enough space, taking into account reserved space */
	if (SB_FREE_BLOCKS(s) - REISERFS_SB(s)->reserved_blocks <
	    amount_needed - reserved_by_us)
		return NO_DISK_SPACE;
	/* should this be if !hint->inode &&  hint->preallocate? */
	/* do you mean hint->formatted_node can be removed ? - Zam */
	/*
	 * hint->formatted_node cannot be removed because we try to access
	 * inode information here, and there is often no inode associated with
	 * metadata allocations - green
	 */

	if (!hint->formatted_node && hint->preallocate) {
		amount_needed = use_preallocated_list_if_available
		    (hint, new_blocknrs, amount_needed);

		/*
		 * We have all the block numbers we need from the
		 * prealloc list
		 */
		if (amount_needed == 0)
			return CARRY_ON;
		new_blocknrs += (initial_amount_needed - amount_needed);
	}

	/* find search start and save it in hint structure */
	determine_search_start(hint, amount_needed);
	if (hint->search_start >= SB_BLOCK_COUNT(s))
		hint->search_start = SB_BLOCK_COUNT(s) - 1;

	/* allocation itself; fill new_blocknrs and preallocation arrays */
	ret = blocknrs_and_prealloc_arrays_from_search_start
	    (hint, new_blocknrs, amount_needed);

	/*
	 * We used prealloc. list to fill (partially) new_blocknrs array.
	 * If final allocation fails we need to return blocks back to
	 * prealloc. list or just free them. -- Zam (I chose second
	 * variant)
	 */
	if (ret != CARRY_ON) {
		while (amount_needed++ < initial_amount_needed) {
			reiserfs_free_block(hint->th, hint->inode,
					    *(--new_blocknrs), 1);
		}
	}
	return ret;
}