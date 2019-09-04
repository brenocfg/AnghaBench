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
struct p9_iattr_dotl {scalar_t__ size; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime_sec; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime_sec; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  valid; } ;
struct p9_fid {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; TYPE_2__ ia_mtime; TYPE_1__ ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PTR_ERR (struct p9_fid*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int p9_client_setattr (struct p9_fid*,struct p9_iattr_dotl*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 
 int v9fs_acl_chmod (struct inode*,struct p9_fid*) ; 
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_invalidate_inode_attr (struct inode*) ; 
 int /*<<< orphan*/  v9fs_mapped_iattr_valid (int) ; 

int v9fs_vfs_setattr_dotl(struct dentry *dentry, struct iattr *iattr)
{
	int retval;
	struct p9_fid *fid;
	struct p9_iattr_dotl p9attr;
	struct inode *inode = d_inode(dentry);

	p9_debug(P9_DEBUG_VFS, "\n");

	retval = setattr_prepare(dentry, iattr);
	if (retval)
		return retval;

	p9attr.valid = v9fs_mapped_iattr_valid(iattr->ia_valid);
	p9attr.mode = iattr->ia_mode;
	p9attr.uid = iattr->ia_uid;
	p9attr.gid = iattr->ia_gid;
	p9attr.size = iattr->ia_size;
	p9attr.atime_sec = iattr->ia_atime.tv_sec;
	p9attr.atime_nsec = iattr->ia_atime.tv_nsec;
	p9attr.mtime_sec = iattr->ia_mtime.tv_sec;
	p9attr.mtime_nsec = iattr->ia_mtime.tv_nsec;

	fid = v9fs_fid_lookup(dentry);
	if (IS_ERR(fid))
		return PTR_ERR(fid);

	/* Write all dirty data */
	if (S_ISREG(inode->i_mode))
		filemap_write_and_wait(inode->i_mapping);

	retval = p9_client_setattr(fid, &p9attr);
	if (retval < 0)
		return retval;

	if ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_read(inode))
		truncate_setsize(inode, iattr->ia_size);

	v9fs_invalidate_inode_attr(inode);
	setattr_copy(inode, iattr);
	mark_inode_dirty(inode);
	if (iattr->ia_valid & ATTR_MODE) {
		/* We also want to update ACL when we update mode bits */
		retval = v9fs_acl_chmod(inode, fid);
		if (retval < 0)
			return retval;
	}
	return 0;
}