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
struct inode {int /*<<< orphan*/  i_count; } ;
struct dentry {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; int /*<<< orphan*/  i_filelock_ref; int /*<<< orphan*/  i_cap_snaps; scalar_t__ i_flushing_caps; scalar_t__ i_dirty_caps; struct ceph_cap* i_auth_cap; } ;
struct ceph_cap {int issued; int implemented; } ;

/* Variables and functions */
 int CEPH_CAP_ANY_WR ; 
 int CEPH_CAP_FILE_CACHE ; 
 int __ceph_caps_file_wanted (struct ceph_inode_info*) ; 
 int __ceph_caps_issued_other (struct ceph_inode_info*,struct ceph_cap*) ; 
 int __ceph_caps_used (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  __ceph_remove_cap (struct ceph_cap*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_cap_string (int) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct dentry* d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  d_prune_aliases (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct ceph_cap*,int,...) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ drop_negative_children (struct dentry*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int trim_caps_cb(struct inode *inode, struct ceph_cap *cap, void *arg)
{
	int *remaining = arg;
	struct ceph_inode_info *ci = ceph_inode(inode);
	int used, wanted, oissued, mine;

	if (*remaining <= 0)
		return -1;

	spin_lock(&ci->i_ceph_lock);
	mine = cap->issued | cap->implemented;
	used = __ceph_caps_used(ci);
	wanted = __ceph_caps_file_wanted(ci);
	oissued = __ceph_caps_issued_other(ci, cap);

	dout("trim_caps_cb %p cap %p mine %s oissued %s used %s wanted %s\n",
	     inode, cap, ceph_cap_string(mine), ceph_cap_string(oissued),
	     ceph_cap_string(used), ceph_cap_string(wanted));
	if (cap == ci->i_auth_cap) {
		if (ci->i_dirty_caps || ci->i_flushing_caps ||
		    !list_empty(&ci->i_cap_snaps))
			goto out;
		if ((used | wanted) & CEPH_CAP_ANY_WR)
			goto out;
		/* Note: it's possible that i_filelock_ref becomes non-zero
		 * after dropping auth caps. It doesn't hurt because reply
		 * of lock mds request will re-add auth caps. */
		if (atomic_read(&ci->i_filelock_ref) > 0)
			goto out;
	}
	/* The inode has cached pages, but it's no longer used.
	 * we can safely drop it */
	if (wanted == 0 && used == CEPH_CAP_FILE_CACHE &&
	    !(oissued & CEPH_CAP_FILE_CACHE)) {
	  used = 0;
	  oissued = 0;
	}
	if ((used | wanted) & ~oissued & mine)
		goto out;   /* we need these caps */

	if (oissued) {
		/* we aren't the only cap.. just remove us */
		__ceph_remove_cap(cap, true);
		(*remaining)--;
	} else {
		struct dentry *dentry;
		/* try dropping referring dentries */
		spin_unlock(&ci->i_ceph_lock);
		dentry = d_find_any_alias(inode);
		if (dentry && drop_negative_children(dentry)) {
			int count;
			dput(dentry);
			d_prune_aliases(inode);
			count = atomic_read(&inode->i_count);
			if (count == 1)
				(*remaining)--;
			dout("trim_caps_cb %p cap %p pruned, count now %d\n",
			     inode, cap, count);
		} else {
			dput(dentry);
		}
		return 0;
	}

out:
	spin_unlock(&ci->i_ceph_lock);
	return 0;
}