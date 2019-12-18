#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wb_lock_cookie {int dummy; } ;
struct page {struct address_space* mapping; } ;
struct inode {int dummy; } ;
struct bdi_writeback {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_dirtied; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_DIRTIED ; 
 int /*<<< orphan*/  WB_DIRTIED ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dec_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_wb_stat (struct bdi_writeback*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 struct bdi_writeback* unlocked_inode_to_wb_begin (struct inode*,struct wb_lock_cookie*) ; 
 int /*<<< orphan*/  unlocked_inode_to_wb_end (struct inode*,struct wb_lock_cookie*) ; 

void account_page_redirty(struct page *page)
{
	struct address_space *mapping = page->mapping;

	if (mapping && mapping_cap_account_dirty(mapping)) {
		struct inode *inode = mapping->host;
		struct bdi_writeback *wb;
		struct wb_lock_cookie cookie = {};

		wb = unlocked_inode_to_wb_begin(inode, &cookie);
		current->nr_dirtied--;
		dec_node_page_state(page, NR_DIRTIED);
		dec_wb_stat(wb, WB_DIRTIED);
		unlocked_inode_to_wb_end(inode, &cookie);
	}
}