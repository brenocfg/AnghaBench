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
struct bdi_writeback {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_ZONE_WRITE_PENDING ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  WB_RECLAIMABLE ; 
 int /*<<< orphan*/  dec_lruvec_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_wb_stat (struct bdi_writeback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 int /*<<< orphan*/  task_io_account_cancelled_write (int /*<<< orphan*/ ) ; 

void account_page_cleaned(struct page *page, struct address_space *mapping,
			  struct bdi_writeback *wb)
{
	if (mapping_cap_account_dirty(mapping)) {
		dec_lruvec_page_state(page, NR_FILE_DIRTY);
		dec_zone_page_state(page, NR_ZONE_WRITE_PENDING);
		dec_wb_stat(wb, WB_RECLAIMABLE);
		task_io_account_cancelled_write(PAGE_SIZE);
	}
}