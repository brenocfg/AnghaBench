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
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 char const* ERR_CAST (struct p9_fid*) ; 
 char const* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  kfree_link ; 
 int p9_client_readlink (struct p9_fid*,char**) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct dentry*) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 

__attribute__((used)) static const char *
v9fs_vfs_get_link_dotl(struct dentry *dentry,
		       struct inode *inode,
		       struct delayed_call *done)
{
	struct p9_fid *fid;
	char *target;
	int retval;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	p9_debug(P9_DEBUG_VFS, "%pd\n", dentry);

	fid = v9fs_fid_lookup(dentry);
	if (IS_ERR(fid))
		return ERR_CAST(fid);
	retval = p9_client_readlink(fid, &target);
	if (retval)
		return ERR_PTR(retval);
	set_delayed_call(done, kfree_link, target);
	return target;
}