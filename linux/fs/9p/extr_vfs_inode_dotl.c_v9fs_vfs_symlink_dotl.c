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
struct p9_qid {int dummy; } ;
struct p9_fid {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {unsigned char* name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_symlink (struct p9_fid*,unsigned char const*,char const*,int /*<<< orphan*/ ,struct p9_qid*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,unsigned char const**,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  v9fs_fid_add (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  v9fs_get_fsgid_for_create (struct p9_fid*) ; 
 struct p9_fid* v9fs_get_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_get_new_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct p9_fid*) ; 
 int /*<<< orphan*/  v9fs_invalidate_inode_attr (struct p9_fid*) ; 
 struct p9_fid* v9fs_parent_fid (struct dentry*) ; 

__attribute__((used)) static int
v9fs_vfs_symlink_dotl(struct inode *dir, struct dentry *dentry,
		const char *symname)
{
	int err;
	kgid_t gid;
	const unsigned char *name;
	struct p9_qid qid;
	struct inode *inode;
	struct p9_fid *dfid;
	struct p9_fid *fid = NULL;
	struct v9fs_session_info *v9ses;

	name = dentry->d_name.name;
	p9_debug(P9_DEBUG_VFS, "%lu,%s,%s\n", dir->i_ino, name, symname);
	v9ses = v9fs_inode2v9ses(dir);

	dfid = v9fs_parent_fid(dentry);
	if (IS_ERR(dfid)) {
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		return err;
	}

	gid = v9fs_get_fsgid_for_create(dir);

	/* Server doesn't alter fid on TSYMLINK. Hence no need to clone it. */
	err = p9_client_symlink(dfid, name, symname, gid, &qid);

	if (err < 0) {
		p9_debug(P9_DEBUG_VFS, "p9_client_symlink failed %d\n", err);
		goto error;
	}

	v9fs_invalidate_inode_attr(dir);
	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) {
		/* Now walk from the parent so we can get an unopened fid. */
		fid = p9_client_walk(dfid, 1, &name, 1);
		if (IS_ERR(fid)) {
			err = PTR_ERR(fid);
			p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n",
				 err);
			fid = NULL;
			goto error;
		}

		/* instantiate inode and assign the unopened fid to dentry */
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		if (IS_ERR(inode)) {
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS, "inode creation failed %d\n",
				 err);
			goto error;
		}
		v9fs_fid_add(dentry, fid);
		d_instantiate(dentry, inode);
		fid = NULL;
		err = 0;
	} else {
		/* Not in cached mode. No need to populate inode with stat */
		inode = v9fs_get_inode(dir->i_sb, S_IFLNK, 0);
		if (IS_ERR(inode)) {
			err = PTR_ERR(inode);
			goto error;
		}
		d_instantiate(dentry, inode);
	}

error:
	if (fid)
		p9_client_clunk(fid);

	return err;
}