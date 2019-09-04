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
struct the_nilfs {int /*<<< orphan*/  ns_inode_lock; } ;
struct nilfs_inode_info {struct buffer_head* i_bh; TYPE_2__* i_root; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifile; } ;
struct TYPE_3__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int nilfs_ifile_get_inode_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_load_inode_block(struct inode *inode, struct buffer_head **pbh)
{
	struct the_nilfs *nilfs = inode->i_sb->s_fs_info;
	struct nilfs_inode_info *ii = NILFS_I(inode);
	int err;

	spin_lock(&nilfs->ns_inode_lock);
	if (ii->i_bh == NULL) {
		spin_unlock(&nilfs->ns_inode_lock);
		err = nilfs_ifile_get_inode_block(ii->i_root->ifile,
						  inode->i_ino, pbh);
		if (unlikely(err))
			return err;
		spin_lock(&nilfs->ns_inode_lock);
		if (ii->i_bh == NULL)
			ii->i_bh = *pbh;
		else {
			brelse(*pbh);
			*pbh = ii->i_bh;
		}
	} else
		*pbh = ii->i_bh;

	get_bh(*pbh);
	spin_unlock(&nilfs->ns_inode_lock);
	return 0;
}