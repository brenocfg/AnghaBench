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
struct list_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_io_list; } ;
struct bdi_writeback {struct list_head b_dirty_time; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  wb_io_lists_depopulated (struct bdi_writeback*) ; 
 int wb_io_lists_populated (struct bdi_writeback*) ; 

__attribute__((used)) static bool inode_io_list_move_locked(struct inode *inode,
				      struct bdi_writeback *wb,
				      struct list_head *head)
{
	assert_spin_locked(&wb->list_lock);

	list_move(&inode->i_io_list, head);

	/* dirty_time doesn't count as dirty_io until expiration */
	if (head != &wb->b_dirty_time)
		return wb_io_lists_populated(wb);

	wb_io_lists_depopulated(wb);
	return false;
}