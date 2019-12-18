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
struct inode {int dummy; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; } ;
struct afs_vnode {int /*<<< orphan*/  rmdir_lock; int /*<<< orphan*/  silly_key; int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_state; TYPE_1__ fid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_LOCK_DELETED ; 
 int DCACHE_NFSFS_RENAMED ; 
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  _enter (char*,struct dentry*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_do_silly_unlink (struct afs_vnode*,struct afs_vnode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_flock_silly_delete ; 
 struct dentry* d_alloc_parallel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_lookup_done (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_flock_ev (struct afs_vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq ; 

int afs_silly_iput(struct dentry *dentry, struct inode *inode)
{
	struct afs_vnode *dvnode = AFS_FS_I(d_inode(dentry->d_parent));
	struct afs_vnode *vnode = AFS_FS_I(inode);
	struct dentry *alias;
	int ret;

	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	_enter("%p{%pd},%llx", dentry, dentry, vnode->fid.vnode);

	down_read(&dvnode->rmdir_lock);

	alias = d_alloc_parallel(dentry->d_parent, &dentry->d_name, &wq);
	if (IS_ERR(alias)) {
		up_read(&dvnode->rmdir_lock);
		return 0;
	}

	if (!d_in_lookup(alias)) {
		/* We raced with lookup...  See if we need to transfer the
		 * sillyrename information to the aliased dentry.
		 */
		ret = 0;
		spin_lock(&alias->d_lock);
		if (d_really_is_positive(alias) &&
		    !(alias->d_flags & DCACHE_NFSFS_RENAMED)) {
			alias->d_flags |= DCACHE_NFSFS_RENAMED;
			ret = 1;
		}
		spin_unlock(&alias->d_lock);
		up_read(&dvnode->rmdir_lock);
		dput(alias);
		return ret;
	}

	/* Stop lock-release from complaining. */
	spin_lock(&vnode->lock);
	vnode->lock_state = AFS_VNODE_LOCK_DELETED;
	trace_afs_flock_ev(vnode, NULL, afs_flock_silly_delete, 0);
	spin_unlock(&vnode->lock);

	afs_do_silly_unlink(dvnode, vnode, dentry, dvnode->silly_key);
	up_read(&dvnode->rmdir_lock);
	d_lookup_done(alias);
	dput(alias);
	return 1;
}