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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_flags; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; scalar_t__ i_ino; TYPE_2__* i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {TYPE_1__* s_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXT4_EA_INODE_FL ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int S_IFREG ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 int /*<<< orphan*/  ext4_file_inode_operations ; 
 int /*<<< orphan*/  ext4_file_operations ; 
 int ext4_inode_attach_jinode (struct inode*) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 struct inode* ext4_new_inode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_aops (struct inode*) ; 
 int /*<<< orphan*/  ext4_xattr_inode_set_class (struct inode*) ; 
 int /*<<< orphan*/  ext4_xattr_inode_set_hash (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_inode_set_ref (struct inode*,int) ; 
 int /*<<< orphan*/  i_gid_read (struct inode*) ; 
 int /*<<< orphan*/  i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static struct inode *ext4_xattr_inode_create(handle_t *handle,
					     struct inode *inode, u32 hash)
{
	struct inode *ea_inode = NULL;
	uid_t owner[2] = { i_uid_read(inode), i_gid_read(inode) };
	int err;

	/*
	 * Let the next inode be the goal, so we try and allocate the EA inode
	 * in the same group, or nearby one.
	 */
	ea_inode = ext4_new_inode(handle, inode->i_sb->s_root->d_inode,
				  S_IFREG | 0600, NULL, inode->i_ino + 1, owner,
				  EXT4_EA_INODE_FL);
	if (!IS_ERR(ea_inode)) {
		ea_inode->i_op = &ext4_file_inode_operations;
		ea_inode->i_fop = &ext4_file_operations;
		ext4_set_aops(ea_inode);
		ext4_xattr_inode_set_class(ea_inode);
		unlock_new_inode(ea_inode);
		ext4_xattr_inode_set_ref(ea_inode, 1);
		ext4_xattr_inode_set_hash(ea_inode, hash);
		err = ext4_mark_inode_dirty(handle, ea_inode);
		if (!err)
			err = ext4_inode_attach_jinode(ea_inode);
		if (err) {
			iput(ea_inode);
			return ERR_PTR(err);
		}

		/*
		 * Xattr inodes are shared therefore quota charging is performed
		 * at a higher level.
		 */
		dquot_free_inode(ea_inode);
		dquot_drop(ea_inode);
		inode_lock(ea_inode);
		ea_inode->i_flags |= S_NOQUOTA;
		inode_unlock(ea_inode);
	}

	return ea_inode;
}