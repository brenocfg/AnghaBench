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
struct autofs_info {int flags; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 unsigned int AUTOFS_EXP_FORCED ; 
 unsigned int AUTOFS_EXP_LEAVES ; 
 int AUTOFS_INF_PENDING ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ autofs_can_expire (struct dentry*,unsigned long,unsigned int) ; 
 struct dentry* autofs_check_leaves (struct vfsmount*,struct dentry*,unsigned long,unsigned int) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 scalar_t__ autofs_mount_busy (struct vfsmount*,struct dentry*,unsigned int) ; 
 int /*<<< orphan*/  autofs_tree_busy (struct vfsmount*,struct dentry*,unsigned long,unsigned int) ; 
 unsigned int d_count (struct dentry*) ; 
 scalar_t__ d_is_symlink (struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*) ; 
 scalar_t__ simple_empty (struct dentry*) ; 

__attribute__((used)) static struct dentry *should_expire(struct dentry *dentry,
				    struct vfsmount *mnt,
				    unsigned long timeout,
				    unsigned int how)
{
	struct autofs_info *ino = autofs_dentry_ino(dentry);
	unsigned int ino_count;

	/* No point expiring a pending mount */
	if (ino->flags & AUTOFS_INF_PENDING)
		return NULL;

	/*
	 * Case 1: (i) indirect mount or top level pseudo direct mount
	 *	   (autofs-4.1).
	 *	   (ii) indirect mount with offset mount, check the "/"
	 *	   offset (autofs-5.0+).
	 */
	if (d_mountpoint(dentry)) {
		pr_debug("checking mountpoint %p %pd\n", dentry, dentry);

		/* Can we umount this guy */
		if (autofs_mount_busy(mnt, dentry, how))
			return NULL;

		/* This isn't a submount so if a forced expire
		 * has been requested, user space handles busy
		 * mounts */
		if (how & AUTOFS_EXP_FORCED)
			return dentry;

		/* Can we expire this guy */
		if (autofs_can_expire(dentry, timeout, how))
			return dentry;
		return NULL;
	}

	if (d_really_is_positive(dentry) && d_is_symlink(dentry)) {
		pr_debug("checking symlink %p %pd\n", dentry, dentry);

		/* Forced expire, user space handles busy mounts */
		if (how & AUTOFS_EXP_FORCED)
			return dentry;

		/*
		 * A symlink can't be "busy" in the usual sense so
		 * just check last used for expire timeout.
		 */
		if (autofs_can_expire(dentry, timeout, how))
			return dentry;
		return NULL;
	}

	if (simple_empty(dentry))
		return NULL;

	/* Case 2: tree mount, expire iff entire tree is not busy */
	if (!(how & AUTOFS_EXP_LEAVES)) {
		/* Not a forced expire? */
		if (!(how & AUTOFS_EXP_FORCED)) {
			/* ref-walk currently on this dentry? */
			ino_count = atomic_read(&ino->count) + 1;
			if (d_count(dentry) > ino_count)
				return NULL;
		}

		if (!autofs_tree_busy(mnt, dentry, timeout, how))
			return dentry;
	/*
	 * Case 3: pseudo direct mount, expire individual leaves
	 *	   (autofs-4.1).
	 */
	} else {
		struct dentry *expired;

		/* Not a forced expire? */
		if (!(how & AUTOFS_EXP_FORCED)) {
			/* ref-walk currently on this dentry? */
			ino_count = atomic_read(&ino->count) + 1;
			if (d_count(dentry) > ino_count)
				return NULL;
		}

		expired = autofs_check_leaves(mnt, dentry, timeout, how);
		if (expired) {
			if (expired == dentry)
				dput(dentry);
			return expired;
		}
	}
	return NULL;
}