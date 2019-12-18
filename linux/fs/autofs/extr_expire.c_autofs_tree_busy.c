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
struct autofs_info {void* last_used; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 unsigned int AUTOFS_EXP_FORCED ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs_can_expire (struct dentry*,unsigned long,unsigned int) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 scalar_t__ autofs_mount_busy (struct vfsmount*,struct dentry*,unsigned int) ; 
 unsigned int d_count (struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* get_next_positive_dentry (struct dentry*,struct dentry*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  simple_positive (struct dentry*) ; 

__attribute__((used)) static int autofs_tree_busy(struct vfsmount *mnt,
			    struct dentry *top,
			    unsigned long timeout,
			    unsigned int how)
{
	struct autofs_info *top_ino = autofs_dentry_ino(top);
	struct dentry *p;

	pr_debug("top %p %pd\n", top, top);

	/* Negative dentry - give up */
	if (!simple_positive(top))
		return 1;

	p = NULL;
	while ((p = get_next_positive_dentry(p, top))) {
		pr_debug("dentry %p %pd\n", p, p);

		/*
		 * Is someone visiting anywhere in the subtree ?
		 * If there's no mount we need to check the usage
		 * count for the autofs dentry.
		 * If the fs is busy update the expiry counter.
		 */
		if (d_mountpoint(p)) {
			if (autofs_mount_busy(mnt, p, how)) {
				top_ino->last_used = jiffies;
				dput(p);
				return 1;
			}
		} else {
			struct autofs_info *ino = autofs_dentry_ino(p);
			unsigned int ino_count = atomic_read(&ino->count);

			/* allow for dget above and top is already dgot */
			if (p == top)
				ino_count += 2;
			else
				ino_count++;

			if (d_count(p) > ino_count) {
				top_ino->last_used = jiffies;
				dput(p);
				return 1;
			}
		}
	}

	/* Forced expire, user space handles busy mounts */
	if (how & AUTOFS_EXP_FORCED)
		return 0;

	/* Timeout of a tree mount is ultimately determined by its top dentry */
	if (!autofs_can_expire(top, timeout, how))
		return 1;

	return 0;
}