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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  GistClearPageHasGarbage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistMarkFollowRight (int /*<<< orphan*/ ) ; 
 scalar_t__ GistPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistPageSetNSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MASK_MARKER ; 
 int /*<<< orphan*/  mask_lp_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_hint_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_lsn_and_checksum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_unused_space (int /*<<< orphan*/ ) ; 

void
gist_mask(char *pagedata, BlockNumber blkno)
{
	Page		page = (Page) pagedata;

	mask_page_lsn_and_checksum(page);

	mask_page_hint_bits(page);
	mask_unused_space(page);

	/*
	 * NSN is nothing but a special purpose LSN. Hence, mask it for the same
	 * reason as mask_page_lsn_and_checksum.
	 */
	GistPageSetNSN(page, (uint64) MASK_MARKER);

	/*
	 * We update F_FOLLOW_RIGHT flag on the left child after writing WAL
	 * record. Hence, mask this flag. See gistplacetopage() for details.
	 */
	GistMarkFollowRight(page);

	if (GistPageIsLeaf(page))
	{
		/*
		 * In gist leaf pages, it is possible to modify the LP_FLAGS without
		 * emitting any WAL record. Hence, mask the line pointer flags. See
		 * gistkillitems() for details.
		 */
		mask_lp_flags(page);
	}

	/*
	 * During gist redo, we never mark a page as garbage. Hence, mask it to
	 * ignore any differences.
	 */
	GistClearPageHasGarbage(page);
}