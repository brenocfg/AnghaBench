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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  u32 ;
struct v9fs_session_info {int dummy; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_ORDWR ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int /*<<< orphan*/  unixmode2p9mode (struct v9fs_session_info*,int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_create (struct v9fs_session_info*,struct inode*,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 
 int /*<<< orphan*/  v9fs_invalidate_inode_attr (struct inode*) ; 

__attribute__((used)) static int
v9fs_vfs_create(struct inode *dir, struct dentry *dentry, umode_t mode,
		bool excl)
{
	struct v9fs_session_info *v9ses = v9fs_inode2v9ses(dir);
	u32 perm = unixmode2p9mode(v9ses, mode);
	struct p9_fid *fid;

	/* P9_OEXCL? */
	fid = v9fs_create(v9ses, dir, dentry, NULL, perm, P9_ORDWR);
	if (IS_ERR(fid))
		return PTR_ERR(fid);

	v9fs_invalidate_inode_attr(dir);
	p9_client_clunk(fid);

	return 0;
}