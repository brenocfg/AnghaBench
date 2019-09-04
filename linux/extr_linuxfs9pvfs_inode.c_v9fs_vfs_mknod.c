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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ U32_MAX_DIGITS ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  unixmode2p9mode (struct v9fs_session_info*,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 
 int v9fs_vfs_mkspecial (struct inode*,struct dentry*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
v9fs_vfs_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t rdev)
{
	struct v9fs_session_info *v9ses = v9fs_inode2v9ses(dir);
	int retval;
	char name[2 + U32_MAX_DIGITS + 1 + U32_MAX_DIGITS + 1];
	u32 perm;

	p9_debug(P9_DEBUG_VFS, " %lu,%pd mode: %hx MAJOR: %u MINOR: %u\n",
		 dir->i_ino, dentry, mode,
		 MAJOR(rdev), MINOR(rdev));

	/* build extension */
	if (S_ISBLK(mode))
		sprintf(name, "b %u %u", MAJOR(rdev), MINOR(rdev));
	else if (S_ISCHR(mode))
		sprintf(name, "c %u %u", MAJOR(rdev), MINOR(rdev));
	else
		*name = 0;

	perm = unixmode2p9mode(v9ses, mode);
	retval = v9fs_vfs_mkspecial(dir, dentry, perm, name);

	return retval;
}