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
struct v9fs_session_info {int dummy; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int AT_REMOVEDIR ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int p9_client_remove (struct p9_fid*) ; 
 int p9_client_unlinkat (struct p9_fid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  v9fs_at_to_dotl_flags (int) ; 
 int /*<<< orphan*/  v9fs_dec_count (struct inode*) ; 
 struct p9_fid* v9fs_fid_clone (struct dentry*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 
 int /*<<< orphan*/  v9fs_invalidate_inode_attr (struct inode*) ; 
 struct p9_fid* v9fs_parent_fid (struct dentry*) ; 
 scalar_t__ v9fs_proto_dotl (struct v9fs_session_info*) ; 

__attribute__((used)) static int v9fs_remove(struct inode *dir, struct dentry *dentry, int flags)
{
	struct inode *inode;
	int retval = -EOPNOTSUPP;
	struct p9_fid *v9fid, *dfid;
	struct v9fs_session_info *v9ses;

	p9_debug(P9_DEBUG_VFS, "inode: %p dentry: %p rmdir: %x\n",
		 dir, dentry, flags);

	v9ses = v9fs_inode2v9ses(dir);
	inode = d_inode(dentry);
	dfid = v9fs_parent_fid(dentry);
	if (IS_ERR(dfid)) {
		retval = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", retval);
		return retval;
	}
	if (v9fs_proto_dotl(v9ses))
		retval = p9_client_unlinkat(dfid, dentry->d_name.name,
					    v9fs_at_to_dotl_flags(flags));
	if (retval == -EOPNOTSUPP) {
		/* Try the one based on path */
		v9fid = v9fs_fid_clone(dentry);
		if (IS_ERR(v9fid))
			return PTR_ERR(v9fid);
		retval = p9_client_remove(v9fid);
	}
	if (!retval) {
		/*
		 * directories on unlink should have zero
		 * link count
		 */
		if (flags & AT_REMOVEDIR) {
			clear_nlink(inode);
			v9fs_dec_count(dir);
		} else
			v9fs_dec_count(inode);

		v9fs_invalidate_inode_attr(inode);
		v9fs_invalidate_inode_attr(dir);
	}
	return retval;
}