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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct backing_dev_info {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_WRITEBACK ; 
 int /*<<< orphan*/  NR_ZONE_WRITE_PENDING ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGECACHE_TAG_TOWRITE ; 
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int TestSetPageWriteback (struct page*) ; 
 int /*<<< orphan*/  WB_WRITEBACK ; 
 scalar_t__ bdi_cap_account_writeback (struct backing_dev_info*) ; 
 int /*<<< orphan*/  inc_lruvec_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_wb_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 struct backing_dev_info* inode_to_bdi (struct inode*) ; 
 int /*<<< orphan*/  inode_to_wb (struct inode*) ; 
 int /*<<< orphan*/  lock_page_memcg (struct page*) ; 
 int mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_use_writeback_tags (struct address_space*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_mark_inode_writeback (struct inode*) ; 
 int /*<<< orphan*/  unlock_page_memcg (struct page*) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int __test_set_page_writeback(struct page *page, bool keep_write)
{
	struct address_space *mapping = page_mapping(page);
	int ret;

	lock_page_memcg(page);
	if (mapping && mapping_use_writeback_tags(mapping)) {
		struct inode *inode = mapping->host;
		struct backing_dev_info *bdi = inode_to_bdi(inode);
		unsigned long flags;

		xa_lock_irqsave(&mapping->i_pages, flags);
		ret = TestSetPageWriteback(page);
		if (!ret) {
			bool on_wblist;

			on_wblist = mapping_tagged(mapping,
						   PAGECACHE_TAG_WRITEBACK);

			radix_tree_tag_set(&mapping->i_pages, page_index(page),
						PAGECACHE_TAG_WRITEBACK);
			if (bdi_cap_account_writeback(bdi))
				inc_wb_stat(inode_to_wb(inode), WB_WRITEBACK);

			/*
			 * We can come through here when swapping anonymous
			 * pages, so we don't necessarily have an inode to track
			 * for sync.
			 */
			if (mapping->host && !on_wblist)
				sb_mark_inode_writeback(mapping->host);
		}
		if (!PageDirty(page))
			radix_tree_tag_clear(&mapping->i_pages, page_index(page),
						PAGECACHE_TAG_DIRTY);
		if (!keep_write)
			radix_tree_tag_clear(&mapping->i_pages, page_index(page),
						PAGECACHE_TAG_TOWRITE);
		xa_unlock_irqrestore(&mapping->i_pages, flags);
	} else {
		ret = TestSetPageWriteback(page);
	}
	if (!ret) {
		inc_lruvec_page_state(page, NR_WRITEBACK);
		inc_zone_page_state(page, NR_ZONE_WRITE_PENDING);
	}
	unlock_page_memcg(page);
	return ret;

}