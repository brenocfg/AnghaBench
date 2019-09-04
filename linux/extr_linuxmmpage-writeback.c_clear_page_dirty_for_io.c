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
struct wb_lock_cookie {int dummy; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct bdi_writeback {int dummy; } ;
struct address_space {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_ZONE_WRITE_PENDING ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int TestClearPageDirty (struct page*) ; 
 int /*<<< orphan*/  WB_RECLAIMABLE ; 
 int /*<<< orphan*/  dec_lruvec_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_wb_stat (struct bdi_writeback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ page_mkclean (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 struct bdi_writeback* unlocked_inode_to_wb_begin (struct inode*,struct wb_lock_cookie*) ; 
 int /*<<< orphan*/  unlocked_inode_to_wb_end (struct inode*,struct wb_lock_cookie*) ; 

int clear_page_dirty_for_io(struct page *page)
{
	struct address_space *mapping = page_mapping(page);
	int ret = 0;

	BUG_ON(!PageLocked(page));

	if (mapping && mapping_cap_account_dirty(mapping)) {
		struct inode *inode = mapping->host;
		struct bdi_writeback *wb;
		struct wb_lock_cookie cookie = {};

		/*
		 * Yes, Virginia, this is indeed insane.
		 *
		 * We use this sequence to make sure that
		 *  (a) we account for dirty stats properly
		 *  (b) we tell the low-level filesystem to
		 *      mark the whole page dirty if it was
		 *      dirty in a pagetable. Only to then
		 *  (c) clean the page again and return 1 to
		 *      cause the writeback.
		 *
		 * This way we avoid all nasty races with the
		 * dirty bit in multiple places and clearing
		 * them concurrently from different threads.
		 *
		 * Note! Normally the "set_page_dirty(page)"
		 * has no effect on the actual dirty bit - since
		 * that will already usually be set. But we
		 * need the side effects, and it can help us
		 * avoid races.
		 *
		 * We basically use the page "master dirty bit"
		 * as a serialization point for all the different
		 * threads doing their things.
		 */
		if (page_mkclean(page))
			set_page_dirty(page);
		/*
		 * We carefully synchronise fault handlers against
		 * installing a dirty pte and marking the page dirty
		 * at this point.  We do this by having them hold the
		 * page lock while dirtying the page, and pages are
		 * always locked coming in here, so we get the desired
		 * exclusion.
		 */
		wb = unlocked_inode_to_wb_begin(inode, &cookie);
		if (TestClearPageDirty(page)) {
			dec_lruvec_page_state(page, NR_FILE_DIRTY);
			dec_zone_page_state(page, NR_ZONE_WRITE_PENDING);
			dec_wb_stat(wb, WB_RECLAIMABLE);
			ret = 1;
		}
		unlocked_inode_to_wb_end(inode, &cookie);
		return ret;
	}
	return TestClearPageDirty(page);
}