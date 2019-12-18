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
struct v9fs_session_info {scalar_t__ cache; } ;
struct TYPE_2__ {scalar_t__ len; unsigned char* name; } ;
struct p9_fid {int /*<<< orphan*/  i_sb; TYPE_1__ d_name; } ;
struct inode {int /*<<< orphan*/  i_sb; TYPE_1__ d_name; } ;
struct dentry {int /*<<< orphan*/  i_sb; TYPE_1__ d_name; } ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOENT ; 
 struct p9_fid* ERR_CAST (struct p9_fid*) ; 
 struct p9_fid* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 struct p9_fid* d_splice_alias (struct p9_fid*,struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,unsigned char const**,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_fid*,struct p9_fid*,struct p9_fid*,unsigned int) ; 
 int /*<<< orphan*/  v9fs_fid_add (struct p9_fid*,struct p9_fid*) ; 
 struct p9_fid* v9fs_get_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_get_new_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct p9_fid*) ; 
 struct p9_fid* v9fs_parent_fid (struct p9_fid*) ; 

struct dentry *v9fs_vfs_lookup(struct inode *dir, struct dentry *dentry,
				      unsigned int flags)
{
	struct dentry *res;
	struct v9fs_session_info *v9ses;
	struct p9_fid *dfid, *fid;
	struct inode *inode;
	const unsigned char *name;

	p9_debug(P9_DEBUG_VFS, "dir: %p dentry: (%pd) %p flags: %x\n",
		 dir, dentry, dentry, flags);

	if (dentry->d_name.len > NAME_MAX)
		return ERR_PTR(-ENAMETOOLONG);

	v9ses = v9fs_inode2v9ses(dir);
	/* We can walk d_parent because we hold the dir->i_mutex */
	dfid = v9fs_parent_fid(dentry);
	if (IS_ERR(dfid))
		return ERR_CAST(dfid);

	/*
	 * Make sure we don't use a wrong inode due to parallel
	 * unlink. For cached mode create calls request for new
	 * inode. But with cache disabled, lookup should do this.
	 */
	name = dentry->d_name.name;
	fid = p9_client_walk(dfid, 1, &name, 1);
	if (fid == ERR_PTR(-ENOENT))
		inode = NULL;
	else if (IS_ERR(fid))
		inode = ERR_CAST(fid);
	else if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		inode = v9fs_get_inode_from_fid(v9ses, fid, dir->i_sb);
	else
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
	/*
	 * If we had a rename on the server and a parallel lookup
	 * for the new name, then make sure we instantiate with
	 * the new name. ie look up for a/b, while on server somebody
	 * moved b under k and client parallely did a lookup for
	 * k/b.
	 */
	res = d_splice_alias(inode, dentry);
	if (!IS_ERR(fid)) {
		if (!res)
			v9fs_fid_add(dentry, fid);
		else if (!IS_ERR(res))
			v9fs_fid_add(res, fid);
		else
			p9_client_clunk(fid);
	}
	return res;
}