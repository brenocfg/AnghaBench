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
struct the_nilfs {int /*<<< orphan*/  ns_inode_lock; } ;
struct nilfs_inode_info {int /*<<< orphan*/  i_state; int /*<<< orphan*/  i_dirty; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_BUSY ; 
 int /*<<< orphan*/  NILFS_I_DIRTY ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nilfs_inode_dirty(struct inode *inode)
{
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct the_nilfs *nilfs = inode->i_sb->s_fs_info;
	int ret = 0;

	if (!list_empty(&ii->i_dirty)) {
		spin_lock(&nilfs->ns_inode_lock);
		ret = test_bit(NILFS_I_DIRTY, &ii->i_state) ||
			test_bit(NILFS_I_BUSY, &ii->i_state);
		spin_unlock(&nilfs->ns_inode_lock);
	}
	return ret;
}