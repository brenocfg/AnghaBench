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
struct mem_cgroup {int dummy; } ;
struct lruvec {int dummy; } ;
struct inode {int dummy; } ;
struct bdi_writeback {int dummy; } ;
struct backing_dev_info {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_WRITEBACK ; 
 int /*<<< orphan*/  NR_WRITTEN ; 
 int /*<<< orphan*/  NR_ZONE_WRITE_PENDING ; 
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 int TestClearPageWriteback (struct page*) ; 
 int /*<<< orphan*/  WB_WRITEBACK ; 
 int /*<<< orphan*/  __unlock_page_memcg (struct mem_cgroup*) ; 
 int /*<<< orphan*/  __wb_writeout_inc (struct bdi_writeback*) ; 
 int /*<<< orphan*/  __xa_clear_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bdi_cap_account_writeback (struct backing_dev_info*) ; 
 int /*<<< orphan*/  dec_lruvec_state (struct lruvec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_wb_stat (struct bdi_writeback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 struct backing_dev_info* inode_to_bdi (struct inode*) ; 
 struct bdi_writeback* inode_to_wb (struct inode*) ; 
 struct mem_cgroup* lock_page_memcg (struct page*) ; 
 int /*<<< orphan*/  mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_use_writeback_tags (struct address_space*) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 int /*<<< orphan*/  sb_clear_inode_writeback (struct inode*) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int test_clear_page_writeback(struct page *page)
{
	struct address_space *mapping = page_mapping(page);
	struct mem_cgroup *memcg;
	struct lruvec *lruvec;
	int ret;

	memcg = lock_page_memcg(page);
	lruvec = mem_cgroup_page_lruvec(page, page_pgdat(page));
	if (mapping && mapping_use_writeback_tags(mapping)) {
		struct inode *inode = mapping->host;
		struct backing_dev_info *bdi = inode_to_bdi(inode);
		unsigned long flags;

		xa_lock_irqsave(&mapping->i_pages, flags);
		ret = TestClearPageWriteback(page);
		if (ret) {
			__xa_clear_mark(&mapping->i_pages, page_index(page),
						PAGECACHE_TAG_WRITEBACK);
			if (bdi_cap_account_writeback(bdi)) {
				struct bdi_writeback *wb = inode_to_wb(inode);

				dec_wb_stat(wb, WB_WRITEBACK);
				__wb_writeout_inc(wb);
			}
		}

		if (mapping->host && !mapping_tagged(mapping,
						     PAGECACHE_TAG_WRITEBACK))
			sb_clear_inode_writeback(mapping->host);

		xa_unlock_irqrestore(&mapping->i_pages, flags);
	} else {
		ret = TestClearPageWriteback(page);
	}
	/*
	 * NOTE: Page might be free now! Writeback doesn't hold a page
	 * reference on its own, it relies on truncation to wait for
	 * the clearing of PG_writeback. The below can only access
	 * page state that is static across allocation cycles.
	 */
	if (ret) {
		dec_lruvec_state(lruvec, NR_WRITEBACK);
		dec_zone_page_state(page, NR_ZONE_WRITE_PENDING);
		inc_node_page_state(page, NR_WRITTEN);
	}
	__unlock_page_memcg(memcg);
	return ret;
}