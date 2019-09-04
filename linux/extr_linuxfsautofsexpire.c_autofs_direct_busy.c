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
struct dentry {int dummy; } ;
struct autofs_info {int /*<<< orphan*/  last_used; } ;

/* Variables and functions */
 unsigned int AUTOFS_EXP_FORCED ; 
 int /*<<< orphan*/  autofs_can_expire (struct dentry*,unsigned long,unsigned int) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  may_umount_tree (struct vfsmount*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*) ; 

__attribute__((used)) static int autofs_direct_busy(struct vfsmount *mnt,
			      struct dentry *top,
			      unsigned long timeout,
			      unsigned int how)
{
	pr_debug("top %p %pd\n", top, top);

	/* Forced expire, user space handles busy mounts */
	if (how & AUTOFS_EXP_FORCED)
		return 0;

	/* If it's busy update the expiry counters */
	if (!may_umount_tree(mnt)) {
		struct autofs_info *ino;

		ino = autofs_dentry_ino(top);
		if (ino)
			ino->last_used = jiffies;
		return 1;
	}

	/* Timeout of a direct mount is determined by its top dentry */
	if (!autofs_can_expire(top, timeout, how))
		return 1;

	return 0;
}