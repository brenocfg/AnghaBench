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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct v9fs_session_info {int dummy; } ;
struct p9_fid {int /*<<< orphan*/  i_sb; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {unsigned char* name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 struct p9_fid* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int P9_DMLINK ; 
 int PTR_ERR (struct p9_fid*) ; 
 struct p9_fid* clone_fid (struct p9_fid*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_fcreate (struct p9_fid*,unsigned char const*,int,int /*<<< orphan*/ ,char*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,unsigned char const**,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  v9fs_fid_add (struct dentry*,struct p9_fid*) ; 
 struct p9_fid* v9fs_get_new_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_parent_fid (struct dentry*) ; 

__attribute__((used)) static struct p9_fid *
v9fs_create(struct v9fs_session_info *v9ses, struct inode *dir,
		struct dentry *dentry, char *extension, u32 perm, u8 mode)
{
	int err;
	const unsigned char *name;
	struct p9_fid *dfid, *ofid, *fid;
	struct inode *inode;

	p9_debug(P9_DEBUG_VFS, "name %pd\n", dentry);

	err = 0;
	ofid = NULL;
	fid = NULL;
	name = dentry->d_name.name;
	dfid = v9fs_parent_fid(dentry);
	if (IS_ERR(dfid)) {
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		return ERR_PTR(err);
	}

	/* clone a fid to use for creation */
	ofid = clone_fid(dfid);
	if (IS_ERR(ofid)) {
		err = PTR_ERR(ofid);
		p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n", err);
		return ERR_PTR(err);
	}

	err = p9_client_fcreate(ofid, name, perm, mode, extension);
	if (err < 0) {
		p9_debug(P9_DEBUG_VFS, "p9_client_fcreate failed %d\n", err);
		goto error;
	}

	if (!(perm & P9_DMLINK)) {
		/* now walk from the parent so we can get unopened fid */
		fid = p9_client_walk(dfid, 1, &name, 1);
		if (IS_ERR(fid)) {
			err = PTR_ERR(fid);
			p9_debug(P9_DEBUG_VFS,
				   "p9_client_walk failed %d\n", err);
			fid = NULL;
			goto error;
		}
		/*
		 * instantiate inode and assign the unopened fid to the dentry
		 */
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		if (IS_ERR(inode)) {
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS,
				   "inode creation failed %d\n", err);
			goto error;
		}
		v9fs_fid_add(dentry, fid);
		d_instantiate(dentry, inode);
	}
	return ofid;
error:
	if (ofid)
		p9_client_clunk(ofid);

	if (fid)
		p9_client_clunk(fid);

	return ERR_PTR(err);
}