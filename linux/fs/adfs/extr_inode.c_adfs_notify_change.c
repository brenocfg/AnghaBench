#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; TYPE_1__ i_mtime; struct super_block* i_sb; } ;
struct iattr {unsigned int ia_valid; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_atime; TYPE_1__ ia_mtime; int /*<<< orphan*/  ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;

/* Variables and functions */
 TYPE_3__* ADFS_I (struct inode*) ; 
 TYPE_2__* ADFS_SB (struct super_block*) ; 
 unsigned int ATTR_ATIME ; 
 unsigned int ATTR_CTIME ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME ; 
 unsigned int ATTR_SIZE ; 
 unsigned int ATTR_UID ; 
 int EPERM ; 
 int /*<<< orphan*/  adfs_atts2mode (struct super_block*,struct inode*) ; 
 int /*<<< orphan*/  adfs_mode2atts (struct super_block*,struct inode*) ; 
 int /*<<< orphan*/  adfs_unix2adfs_time (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
adfs_notify_change(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	struct super_block *sb = inode->i_sb;
	unsigned int ia_valid = attr->ia_valid;
	int error;
	
	error = setattr_prepare(dentry, attr);

	/*
	 * we can't change the UID or GID of any file -
	 * we have a global UID/GID in the superblock
	 */
	if ((ia_valid & ATTR_UID && !uid_eq(attr->ia_uid, ADFS_SB(sb)->s_uid)) ||
	    (ia_valid & ATTR_GID && !gid_eq(attr->ia_gid, ADFS_SB(sb)->s_gid)))
		error = -EPERM;

	if (error)
		goto out;

	/* XXX: this is missing some actual on-disk truncation.. */
	if (ia_valid & ATTR_SIZE)
		truncate_setsize(inode, attr->ia_size);

	if (ia_valid & ATTR_MTIME) {
		inode->i_mtime = attr->ia_mtime;
		adfs_unix2adfs_time(inode, attr->ia_mtime.tv_sec);
	}
	/*
	 * FIXME: should we make these == to i_mtime since we don't
	 * have the ability to represent them in our filesystem?
	 */
	if (ia_valid & ATTR_ATIME)
		inode->i_atime = attr->ia_atime;
	if (ia_valid & ATTR_CTIME)
		inode->i_ctime = attr->ia_ctime;
	if (ia_valid & ATTR_MODE) {
		ADFS_I(inode)->attr = adfs_mode2atts(sb, inode);
		inode->i_mode = adfs_atts2mode(sb, inode);
	}

	/*
	 * FIXME: should we be marking this inode dirty even if
	 * we don't have any metadata to write back?
	 */
	if (ia_valid & (ATTR_SIZE | ATTR_MTIME | ATTR_MODE))
		mark_inode_dirty(inode);
out:
	return error;
}