#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ btpo_cycleid; int /*<<< orphan*/  btpo_flags; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  TYPE_1__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BTP_HAS_GARBAGE ; 
 int /*<<< orphan*/  BTP_SPLIT_END ; 
 scalar_t__ P_ISDELETED (TYPE_1__*) ; 
 scalar_t__ P_ISLEAF (TYPE_1__*) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_lp_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_content (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_hint_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_lsn_and_checksum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_unused_space (int /*<<< orphan*/ ) ; 

void
btree_mask(char *pagedata, BlockNumber blkno)
{
	Page		page = (Page) pagedata;
	BTPageOpaque maskopaq;

	mask_page_lsn_and_checksum(page);

	mask_page_hint_bits(page);
	mask_unused_space(page);

	maskopaq = (BTPageOpaque) PageGetSpecialPointer(page);

	if (P_ISDELETED(maskopaq))
	{
		/*
		 * Mask page content on a DELETED page since it will be re-initialized
		 * during replay. See btree_xlog_unlink_page() for details.
		 */
		mask_page_content(page);
	}
	else if (P_ISLEAF(maskopaq))
	{
		/*
		 * In btree leaf pages, it is possible to modify the LP_FLAGS without
		 * emitting any WAL record. Hence, mask the line pointer flags. See
		 * _bt_killitems(), _bt_check_unique() for details.
		 */
		mask_lp_flags(page);
	}

	/*
	 * BTP_HAS_GARBAGE is just an un-logged hint bit. So, mask it. See
	 * _bt_killitems(), _bt_check_unique() for details.
	 */
	maskopaq->btpo_flags &= ~BTP_HAS_GARBAGE;

	/*
	 * During replay of a btree page split, we don't set the BTP_SPLIT_END
	 * flag of the right sibling and initialize the cycle_id to 0 for the same
	 * page. See btree_xlog_split() for details.
	 */
	maskopaq->btpo_flags &= ~BTP_SPLIT_END;
	maskopaq->btpo_cycleid = 0;
}