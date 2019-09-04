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
typedef  scalar_t__ u32 ;
struct inode {scalar_t__ i_ino; scalar_t__ i_generation; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int i_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EXT4_EA_INODE_FL ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_IGET_NORMAL ; 
 int /*<<< orphan*/  EXT4_STATE_LUSTRE_EA_INODE ; 
 scalar_t__ EXT4_XATTR_INODE_GET_PARENT (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 struct inode* ext4_iget (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_xattr_inode_get_hash (struct inode*) ; 
 int /*<<< orphan*/  ext4_xattr_inode_set_class (struct inode*) ; 
 int /*<<< orphan*/  ext4_xattr_inode_set_ref (struct inode*,int) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 

__attribute__((used)) static int ext4_xattr_inode_iget(struct inode *parent, unsigned long ea_ino,
				 u32 ea_inode_hash, struct inode **ea_inode)
{
	struct inode *inode;
	int err;

	inode = ext4_iget(parent->i_sb, ea_ino, EXT4_IGET_NORMAL);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		ext4_error(parent->i_sb,
			   "error while reading EA inode %lu err=%d", ea_ino,
			   err);
		return err;
	}

	if (is_bad_inode(inode)) {
		ext4_error(parent->i_sb,
			   "error while reading EA inode %lu is_bad_inode",
			   ea_ino);
		err = -EIO;
		goto error;
	}

	if (!(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL)) {
		ext4_error(parent->i_sb,
			   "EA inode %lu does not have EXT4_EA_INODE_FL flag",
			    ea_ino);
		err = -EINVAL;
		goto error;
	}

	ext4_xattr_inode_set_class(inode);

	/*
	 * Check whether this is an old Lustre-style xattr inode. Lustre
	 * implementation does not have hash validation, rather it has a
	 * backpointer from ea_inode to the parent inode.
	 */
	if (ea_inode_hash != ext4_xattr_inode_get_hash(inode) &&
	    EXT4_XATTR_INODE_GET_PARENT(inode) == parent->i_ino &&
	    inode->i_generation == parent->i_generation) {
		ext4_set_inode_state(inode, EXT4_STATE_LUSTRE_EA_INODE);
		ext4_xattr_inode_set_ref(inode, 1);
	} else {
		inode_lock(inode);
		inode->i_flags |= S_NOQUOTA;
		inode_unlock(inode);
	}

	*ea_inode = inode;
	return 0;
error:
	iput(inode);
	return err;
}