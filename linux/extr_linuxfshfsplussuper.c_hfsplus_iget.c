#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int i_state; scalar_t__ i_ino; int /*<<< orphan*/  i_sb; } ;
struct hfs_find_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  opencnt; int /*<<< orphan*/ * rsrc_inode; scalar_t__ extent_state; scalar_t__ flags; int /*<<< orphan*/  extents_lock; int /*<<< orphan*/  open_dir_lock; int /*<<< orphan*/  open_dir_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  cat_tree; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 scalar_t__ HFSPLUS_FIRSTUSER_CNID ; 
 TYPE_2__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_ROOT_CNID ; 
 TYPE_1__* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int I_NEW ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int hfsplus_cat_read_inode (struct inode*,struct hfs_find_data*) ; 
 int hfsplus_find_cat (int /*<<< orphan*/ ,scalar_t__,struct hfs_find_data*) ; 
 int hfsplus_system_read_inode (struct inode*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *hfsplus_iget(struct super_block *sb, unsigned long ino)
{
	struct hfs_find_data fd;
	struct inode *inode;
	int err;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	INIT_LIST_HEAD(&HFSPLUS_I(inode)->open_dir_list);
	spin_lock_init(&HFSPLUS_I(inode)->open_dir_lock);
	mutex_init(&HFSPLUS_I(inode)->extents_lock);
	HFSPLUS_I(inode)->flags = 0;
	HFSPLUS_I(inode)->extent_state = 0;
	HFSPLUS_I(inode)->rsrc_inode = NULL;
	atomic_set(&HFSPLUS_I(inode)->opencnt, 0);

	if (inode->i_ino >= HFSPLUS_FIRSTUSER_CNID ||
	    inode->i_ino == HFSPLUS_ROOT_CNID) {
		err = hfs_find_init(HFSPLUS_SB(inode->i_sb)->cat_tree, &fd);
		if (!err) {
			err = hfsplus_find_cat(inode->i_sb, inode->i_ino, &fd);
			if (!err)
				err = hfsplus_cat_read_inode(inode, &fd);
			hfs_find_exit(&fd);
		}
	} else {
		err = hfsplus_system_read_inode(inode);
	}

	if (err) {
		iget_failed(inode);
		return ERR_PTR(err);
	}

	unlock_new_inode(inode);
	return inode;
}