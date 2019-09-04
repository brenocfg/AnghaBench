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
struct p9_fid {int fid; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DMLINK ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  U32_MAX_DIGITS ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct p9_fid* v9fs_fid_clone (struct dentry*) ; 
 int /*<<< orphan*/  v9fs_invalidate_inode_attr (struct inode*) ; 
 int /*<<< orphan*/  v9fs_refresh_inode (struct p9_fid*,int /*<<< orphan*/ ) ; 
 int v9fs_vfs_mkspecial (struct inode*,struct dentry*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
v9fs_vfs_link(struct dentry *old_dentry, struct inode *dir,
	      struct dentry *dentry)
{
	int retval;
	char name[1 + U32_MAX_DIGITS + 2]; /* sign + number + \n + \0 */
	struct p9_fid *oldfid;

	p9_debug(P9_DEBUG_VFS, " %lu,%pd,%pd\n",
		 dir->i_ino, dentry, old_dentry);

	oldfid = v9fs_fid_clone(old_dentry);
	if (IS_ERR(oldfid))
		return PTR_ERR(oldfid);

	sprintf(name, "%d\n", oldfid->fid);
	retval = v9fs_vfs_mkspecial(dir, dentry, P9_DMLINK, name);
	if (!retval) {
		v9fs_refresh_inode(oldfid, d_inode(old_dentry));
		v9fs_invalidate_inode_attr(dir);
	}
	p9_client_clunk(oldfid);
	return retval;
}