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
struct vfsmount {int dummy; } ;
struct path {struct vfsmount* mnt; struct dentry* dentry; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  type; } ;
struct autofs_info {int /*<<< orphan*/  last_used; } ;

/* Variables and functions */
 unsigned int AUTOFS_EXP_FORCED ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_indirect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  follow_down_one (struct path*) ; 
 scalar_t__ is_autofs_dentry (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  may_umount_tree (struct vfsmount*) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int autofs_mount_busy(struct vfsmount *mnt,
			     struct dentry *dentry, unsigned int how)
{
	struct dentry *top = dentry;
	struct path path = {.mnt = mnt, .dentry = dentry};
	int status = 1;

	pr_debug("dentry %p %pd\n", dentry, dentry);

	path_get(&path);

	if (!follow_down_one(&path))
		goto done;

	if (is_autofs_dentry(path.dentry)) {
		struct autofs_sb_info *sbi = autofs_sbi(path.dentry->d_sb);

		/* This is an autofs submount, we can't expire it */
		if (autofs_type_indirect(sbi->type))
			goto done;
	}

	/* Not a submount, has a forced expire been requested */
	if (how & AUTOFS_EXP_FORCED) {
		status = 0;
		goto done;
	}

	/* Update the expiry counter if fs is busy */
	if (!may_umount_tree(path.mnt)) {
		struct autofs_info *ino;

		ino = autofs_dentry_ino(top);
		ino->last_used = jiffies;
		goto done;
	}

	status = 0;
done:
	pr_debug("returning = %d\n", status);
	path_put(&path);
	return status;
}