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
typedef  int /*<<< orphan*/  u32 ;
struct path_cond {int /*<<< orphan*/  mode; int /*<<< orphan*/  uid; } ;
struct path {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int common_perm_dir_dentry (char const*,struct path const*,struct dentry*,int /*<<< orphan*/ ,struct path_cond*) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  path_mediated_fs (struct dentry*) ; 

__attribute__((used)) static int common_perm_rm(const char *op, const struct path *dir,
			  struct dentry *dentry, u32 mask)
{
	struct inode *inode = d_backing_inode(dentry);
	struct path_cond cond = { };

	if (!inode || !path_mediated_fs(dentry))
		return 0;

	cond.uid = inode->i_uid;
	cond.mode = inode->i_mode;

	return common_perm_dir_dentry(op, dir, dentry, mask, &cond);
}