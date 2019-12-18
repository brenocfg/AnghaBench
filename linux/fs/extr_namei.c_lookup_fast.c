#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct path {struct dentry* dentry; struct vfsmount* mnt; } ;
struct TYPE_2__ {struct dentry* dentry; struct vfsmount* mnt; } ;
struct nameidata {int flags; int /*<<< orphan*/  last; int /*<<< orphan*/  seq; TYPE_1__ path; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_seq; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 int LOOKUP_RCU ; 
 struct dentry* __d_lookup (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* __d_lookup_rcu (struct dentry*,int /*<<< orphan*/ *,unsigned int*) ; 
 int __follow_mount_rcu (struct nameidata*,struct path*,struct inode**,unsigned int*) ; 
 int __read_seqcount_retry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 int d_is_negative (struct dentry*) ; 
 int d_revalidate (struct dentry*,int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int follow_managed (struct path*,struct nameidata*) ; 
 scalar_t__ likely (int) ; 
 int read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ unlazy_child (struct nameidata*,struct dentry*,unsigned int) ; 
 scalar_t__ unlazy_walk (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lookup_fast(struct nameidata *nd,
		       struct path *path, struct inode **inode,
		       unsigned *seqp)
{
	struct vfsmount *mnt = nd->path.mnt;
	struct dentry *dentry, *parent = nd->path.dentry;
	int status = 1;
	int err;

	/*
	 * Rename seqlock is not required here because in the off chance
	 * of a false negative due to a concurrent rename, the caller is
	 * going to fall back to non-racy lookup.
	 */
	if (nd->flags & LOOKUP_RCU) {
		unsigned seq;
		bool negative;
		dentry = __d_lookup_rcu(parent, &nd->last, &seq);
		if (unlikely(!dentry)) {
			if (unlazy_walk(nd))
				return -ECHILD;
			return 0;
		}

		/*
		 * This sequence count validates that the inode matches
		 * the dentry name information from lookup.
		 */
		*inode = d_backing_inode(dentry);
		negative = d_is_negative(dentry);
		if (unlikely(read_seqcount_retry(&dentry->d_seq, seq)))
			return -ECHILD;

		/*
		 * This sequence count validates that the parent had no
		 * changes while we did the lookup of the dentry above.
		 *
		 * The memory barrier in read_seqcount_begin of child is
		 *  enough, we can use __read_seqcount_retry here.
		 */
		if (unlikely(__read_seqcount_retry(&parent->d_seq, nd->seq)))
			return -ECHILD;

		*seqp = seq;
		status = d_revalidate(dentry, nd->flags);
		if (likely(status > 0)) {
			/*
			 * Note: do negative dentry check after revalidation in
			 * case that drops it.
			 */
			if (unlikely(negative))
				return -ENOENT;
			path->mnt = mnt;
			path->dentry = dentry;
			if (likely(__follow_mount_rcu(nd, path, inode, seqp)))
				return 1;
		}
		if (unlazy_child(nd, dentry, seq))
			return -ECHILD;
		if (unlikely(status == -ECHILD))
			/* we'd been told to redo it in non-rcu mode */
			status = d_revalidate(dentry, nd->flags);
	} else {
		dentry = __d_lookup(parent, &nd->last);
		if (unlikely(!dentry))
			return 0;
		status = d_revalidate(dentry, nd->flags);
	}
	if (unlikely(status <= 0)) {
		if (!status)
			d_invalidate(dentry);
		dput(dentry);
		return status;
	}
	if (unlikely(d_is_negative(dentry))) {
		dput(dentry);
		return -ENOENT;
	}

	path->mnt = mnt;
	path->dentry = dentry;
	err = follow_managed(path, nd);
	if (likely(err > 0))
		*inode = d_backing_inode(path->dentry);
	return err;
}