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
struct inode {int /*<<< orphan*/  i_io_list; } ;
struct bdi_writeback {int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_io_lists_depopulated (struct bdi_writeback*) ; 

__attribute__((used)) static void inode_io_list_del_locked(struct inode *inode,
				     struct bdi_writeback *wb)
{
	assert_spin_locked(&wb->list_lock);

	list_del_init(&inode->i_io_list);
	wb_io_lists_depopulated(wb);
}