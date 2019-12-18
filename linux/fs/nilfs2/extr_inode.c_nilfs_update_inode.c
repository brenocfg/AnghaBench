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
struct nilfs_inode_info {int /*<<< orphan*/  i_state; TYPE_1__* i_root; } ;
struct nilfs_inode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_4__ {int /*<<< orphan*/  mi_entry_size; } ;
struct TYPE_3__ {struct inode* ifile; } ;

/* Variables and functions */
 int I_DIRTY_DATASYNC ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_INODE_SYNC ; 
 int /*<<< orphan*/  NILFS_I_NEW ; 
 TYPE_2__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  memset (struct nilfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nilfs_inode* nilfs_ifile_map_inode (struct inode*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_ifile_unmap_inode (struct inode*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_write_inode_common (struct inode*,struct nilfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nilfs_update_inode(struct inode *inode, struct buffer_head *ibh, int flags)
{
	ino_t ino = inode->i_ino;
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct inode *ifile = ii->i_root->ifile;
	struct nilfs_inode *raw_inode;

	raw_inode = nilfs_ifile_map_inode(ifile, ino, ibh);

	if (test_and_clear_bit(NILFS_I_NEW, &ii->i_state))
		memset(raw_inode, 0, NILFS_MDT(ifile)->mi_entry_size);
	if (flags & I_DIRTY_DATASYNC)
		set_bit(NILFS_I_INODE_SYNC, &ii->i_state);

	nilfs_write_inode_common(inode, raw_inode, 0);
		/*
		 * XXX: call with has_bmap = 0 is a workaround to avoid
		 * deadlock of bmap.  This delays update of i_bmap to just
		 * before writing.
		 */

	nilfs_ifile_unmap_inode(ifile, ino, ibh);
}