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
struct v9fs_session_info {int dummy; } ;
struct v9fs_inode {int cache_validity; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 unsigned int LOOKUP_RCU ; 
 int PTR_ERR (struct p9_fid*) ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int V9FS_INO_INVALID_ATTR ; 
 struct inode* d_inode (struct dentry*) ; 
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 
 scalar_t__ v9fs_proto_dotl (struct v9fs_session_info*) ; 
 int v9fs_refresh_inode (struct p9_fid*,struct inode*) ; 
 int v9fs_refresh_inode_dotl (struct p9_fid*,struct inode*) ; 

__attribute__((used)) static int v9fs_lookup_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct p9_fid *fid;
	struct inode *inode;
	struct v9fs_inode *v9inode;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	inode = d_inode(dentry);
	if (!inode)
		goto out_valid;

	v9inode = V9FS_I(inode);
	if (v9inode->cache_validity & V9FS_INO_INVALID_ATTR) {
		int retval;
		struct v9fs_session_info *v9ses;
		fid = v9fs_fid_lookup(dentry);
		if (IS_ERR(fid))
			return PTR_ERR(fid);

		v9ses = v9fs_inode2v9ses(inode);
		if (v9fs_proto_dotl(v9ses))
			retval = v9fs_refresh_inode_dotl(fid, inode);
		else
			retval = v9fs_refresh_inode(fid, inode);
		if (retval == -ENOENT)
			return 0;
		if (retval < 0)
			return retval;
	}
out_valid:
	return 1;
}