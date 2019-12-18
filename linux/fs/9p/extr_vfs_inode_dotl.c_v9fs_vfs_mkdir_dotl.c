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
typedef  int umode_t ;
struct v9fs_session_info {scalar_t__ cache; } ;
struct posix_acl {int dummy; } ;
struct p9_qid {int dummy; } ;
struct p9_fid {int i_mode; int /*<<< orphan*/  i_sb; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {unsigned char* name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PTR_ERR (struct p9_fid*) ; 
 int S_IFDIR ; 
 int S_ISGID ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  inc_nlink (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_mkdir_dotl (struct p9_fid*,unsigned char const*,int,int /*<<< orphan*/ ,struct p9_qid*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,unsigned char const**,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 
 int v9fs_acl_mode (struct p9_fid*,int*,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  v9fs_fid_add (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  v9fs_get_fsgid_for_create (struct p9_fid*) ; 
 struct p9_fid* v9fs_get_inode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_get_new_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct p9_fid*) ; 
 int /*<<< orphan*/  v9fs_invalidate_inode_attr (struct p9_fid*) ; 
 struct p9_fid* v9fs_parent_fid (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_put_acl (struct posix_acl*,struct posix_acl*) ; 
 int /*<<< orphan*/  v9fs_set_create_acl (struct p9_fid*,struct p9_fid*,struct posix_acl*,struct posix_acl*) ; 

__attribute__((used)) static int v9fs_vfs_mkdir_dotl(struct inode *dir,
			       struct dentry *dentry, umode_t omode)
{
	int err;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid = NULL, *dfid = NULL;
	kgid_t gid;
	const unsigned char *name;
	umode_t mode;
	struct inode *inode;
	struct p9_qid qid;
	struct posix_acl *dacl = NULL, *pacl = NULL;

	p9_debug(P9_DEBUG_VFS, "name %pd\n", dentry);
	err = 0;
	v9ses = v9fs_inode2v9ses(dir);

	omode |= S_IFDIR;
	if (dir->i_mode & S_ISGID)
		omode |= S_ISGID;

	dfid = v9fs_parent_fid(dentry);
	if (IS_ERR(dfid)) {
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		dfid = NULL;
		goto error;
	}

	gid = v9fs_get_fsgid_for_create(dir);
	mode = omode;
	/* Update mode based on ACL value */
	err = v9fs_acl_mode(dir, &mode, &dacl, &pacl);
	if (err) {
		p9_debug(P9_DEBUG_VFS, "Failed to get acl values in mkdir %d\n",
			 err);
		goto error;
	}
	name = dentry->d_name.name;
	err = p9_client_mkdir_dotl(dfid, name, mode, gid, &qid);
	if (err < 0)
		goto error;

	fid = p9_client_walk(dfid, 1, &name, 1);
	if (IS_ERR(fid)) {
		err = PTR_ERR(fid);
		p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n",
			 err);
		fid = NULL;
		goto error;
	}

	/* instantiate inode and assign the unopened fid to the dentry */
	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) {
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		if (IS_ERR(inode)) {
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS, "inode creation failed %d\n",
				 err);
			goto error;
		}
		v9fs_fid_add(dentry, fid);
		v9fs_set_create_acl(inode, fid, dacl, pacl);
		d_instantiate(dentry, inode);
		fid = NULL;
		err = 0;
	} else {
		/*
		 * Not in cached mode. No need to populate
		 * inode with stat. We need to get an inode
		 * so that we can set the acl with dentry
		 */
		inode = v9fs_get_inode(dir->i_sb, mode, 0);
		if (IS_ERR(inode)) {
			err = PTR_ERR(inode);
			goto error;
		}
		v9fs_set_create_acl(inode, fid, dacl, pacl);
		d_instantiate(dentry, inode);
	}
	inc_nlink(dir);
	v9fs_invalidate_inode_attr(dir);
error:
	if (fid)
		p9_client_clunk(fid);
	v9fs_put_acl(dacl, pacl);
	return err;
}