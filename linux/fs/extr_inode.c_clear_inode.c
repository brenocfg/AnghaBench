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
struct TYPE_2__ {int nrpages; int nrexceptional; int /*<<< orphan*/  private_list; int /*<<< orphan*/  i_pages; } ;
struct inode {int i_state; int /*<<< orphan*/  i_wb_list; TYPE_1__ i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_CLEAR ; 
 int I_FREEING ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

void clear_inode(struct inode *inode)
{
	/*
	 * We have to cycle the i_pages lock here because reclaim can be in the
	 * process of removing the last page (in __delete_from_page_cache())
	 * and we must not free the mapping under it.
	 */
	xa_lock_irq(&inode->i_data.i_pages);
	BUG_ON(inode->i_data.nrpages);
	BUG_ON(inode->i_data.nrexceptional);
	xa_unlock_irq(&inode->i_data.i_pages);
	BUG_ON(!list_empty(&inode->i_data.private_list));
	BUG_ON(!(inode->i_state & I_FREEING));
	BUG_ON(inode->i_state & I_CLEAR);
	BUG_ON(!list_empty(&inode->i_wb_list));
	/* don't need i_lock here, no concurrent mods to i_state */
	inode->i_state = I_FREEING | I_CLEAR;
}