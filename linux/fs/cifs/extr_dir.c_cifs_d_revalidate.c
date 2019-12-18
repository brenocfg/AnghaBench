#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; } ;
struct TYPE_3__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (TYPE_1__*) ; 
 TYPE_1__* CIFS_I (struct inode*) ; 
 int DCACHE_NEED_AUTOMOUNT ; 
 int ECHILD ; 
 scalar_t__ HZ ; 
 scalar_t__ IS_AUTOMOUNT (struct inode*) ; 
 unsigned int LOOKUP_CREATE ; 
 unsigned int LOOKUP_RCU ; 
 unsigned int LOOKUP_RENAME_TARGET ; 
 unsigned int LOOKUP_REVAL ; 
 scalar_t__ cifs_get_time (struct dentry*) ; 
 scalar_t__ cifs_revalidate_dentry (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lookupCacheEnabled ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
cifs_d_revalidate(struct dentry *direntry, unsigned int flags)
{
	struct inode *inode;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	if (d_really_is_positive(direntry)) {
		inode = d_inode(direntry);
		if ((flags & LOOKUP_REVAL) && !CIFS_CACHE_READ(CIFS_I(inode)))
			CIFS_I(inode)->time = 0; /* force reval */

		if (cifs_revalidate_dentry(direntry))
			return 0;
		else {
			/*
			 * If the inode wasn't known to be a dfs entry when
			 * the dentry was instantiated, such as when created
			 * via ->readdir(), it needs to be set now since the
			 * attributes will have been updated by
			 * cifs_revalidate_dentry().
			 */
			if (IS_AUTOMOUNT(inode) &&
			   !(direntry->d_flags & DCACHE_NEED_AUTOMOUNT)) {
				spin_lock(&direntry->d_lock);
				direntry->d_flags |= DCACHE_NEED_AUTOMOUNT;
				spin_unlock(&direntry->d_lock);
			}

			return 1;
		}
	}

	/*
	 * This may be nfsd (or something), anyway, we can't see the
	 * intent of this. So, since this can be for creation, drop it.
	 */
	if (!flags)
		return 0;

	/*
	 * Drop the negative dentry, in order to make sure to use the
	 * case sensitive name which is specified by user if this is
	 * for creation.
	 */
	if (flags & (LOOKUP_CREATE | LOOKUP_RENAME_TARGET))
		return 0;

	if (time_after(jiffies, cifs_get_time(direntry) + HZ) || !lookupCacheEnabled)
		return 0;

	return 1;
}