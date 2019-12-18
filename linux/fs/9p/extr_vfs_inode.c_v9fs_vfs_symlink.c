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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DMSYMLINK ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct dentry*,char const*) ; 
 int v9fs_vfs_mkspecial (struct inode*,struct dentry*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
v9fs_vfs_symlink(struct inode *dir, struct dentry *dentry, const char *symname)
{
	p9_debug(P9_DEBUG_VFS, " %lu,%pd,%s\n",
		 dir->i_ino, dentry, symname);

	return v9fs_vfs_mkspecial(dir, dentry, P9_DMSYMLINK, symname);
}