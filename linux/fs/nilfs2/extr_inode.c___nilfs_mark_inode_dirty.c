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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {TYPE_1__* i_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifile; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 TYPE_2__* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int nilfs_load_inode_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nilfs_update_inode (struct inode*,struct buffer_head*,int) ; 
 scalar_t__ unlikely (int) ; 

int __nilfs_mark_inode_dirty(struct inode *inode, int flags)
{
	struct buffer_head *ibh;
	int err;

	err = nilfs_load_inode_block(inode, &ibh);
	if (unlikely(err)) {
		nilfs_msg(inode->i_sb, KERN_WARNING,
			  "cannot mark inode dirty (ino=%lu): error %d loading inode block",
			  inode->i_ino, err);
		return err;
	}
	nilfs_update_inode(inode, ibh, flags);
	mark_buffer_dirty(ibh);
	nilfs_mdt_mark_dirty(NILFS_I(inode)->i_root->ifile);
	brelse(ibh);
	return 0;
}