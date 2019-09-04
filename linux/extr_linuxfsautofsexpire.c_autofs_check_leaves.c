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

/* Variables and functions */
 unsigned int AUTOFS_EXP_FORCED ; 
 scalar_t__ autofs_can_expire (struct dentry*,unsigned long,unsigned int) ; 
 scalar_t__ autofs_mount_busy (struct vfsmount*,struct dentry*,unsigned int) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 struct dentry* get_next_positive_dentry (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*) ; 

__attribute__((used)) static struct dentry *autofs_check_leaves(struct vfsmount *mnt,
					  struct dentry *parent,
					  unsigned long timeout,
					  unsigned int how)
{
	struct dentry *p;

	pr_debug("parent %p %pd\n", parent, parent);

	p = NULL;
	while ((p = get_next_positive_dentry(p, parent))) {
		pr_debug("dentry %p %pd\n", p, p);

		if (d_mountpoint(p)) {
			/* Can we umount this guy */
			if (autofs_mount_busy(mnt, p, how))
				continue;

			/* This isn't a submount so if a forced expire
			 * has been requested, user space handles busy
			 * mounts */
			if (how & AUTOFS_EXP_FORCED)
				return p;

			/* Can we expire this guy */
			if (autofs_can_expire(p, timeout, how))
				return p;
		}
	}
	return NULL;
}