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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct bdi_writeback {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_dirtied; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_DIRTIED ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_ZONE_WRITE_PENDING ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WB_DIRTIED ; 
 int /*<<< orphan*/  WB_RECLAIMABLE ; 
 int /*<<< orphan*/  __inc_lruvec_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdp_ratelimits ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  inc_wb_stat (struct bdi_writeback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_attach_wb (struct inode*,struct page*) ; 
 struct bdi_writeback* inode_to_wb (struct inode*) ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 int /*<<< orphan*/  mem_cgroup_track_foreign_dirty (struct page*,struct bdi_writeback*) ; 
 int /*<<< orphan*/  task_io_account_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_writeback_dirty_page (struct page*,struct address_space*) ; 

void account_page_dirtied(struct page *page, struct address_space *mapping)
{
	struct inode *inode = mapping->host;

	trace_writeback_dirty_page(page, mapping);

	if (mapping_cap_account_dirty(mapping)) {
		struct bdi_writeback *wb;

		inode_attach_wb(inode, page);
		wb = inode_to_wb(inode);

		__inc_lruvec_page_state(page, NR_FILE_DIRTY);
		__inc_zone_page_state(page, NR_ZONE_WRITE_PENDING);
		__inc_node_page_state(page, NR_DIRTIED);
		inc_wb_stat(wb, WB_RECLAIMABLE);
		inc_wb_stat(wb, WB_DIRTIED);
		task_io_account_write(PAGE_SIZE);
		current->nr_dirtied++;
		this_cpu_inc(bdp_ratelimits);

		mem_cgroup_track_foreign_dirty(page, wb);
	}
}