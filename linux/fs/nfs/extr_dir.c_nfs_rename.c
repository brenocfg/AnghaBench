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
struct rpc_task {int tk_status; scalar_t__ tk_calldata; } ;
struct nfs_renamedata {int cancelled; } ;
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_parent; } ;
struct TYPE_2__ {int cache_validity; int /*<<< orphan*/  attr_gencount; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_CHANGE ; 
 int NFS_INO_INVALID_CTIME ; 
 int NFS_INO_REVAL_FORCED ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS ; 
 struct dentry* d_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int d_count (struct dentry*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct dentry*,struct dentry*,int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct rpc_task* nfs_async_rename (struct inode*,struct inode*,struct dentry*,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_dentry_handle_enoent (struct dentry*) ; 
 int /*<<< orphan*/  nfs_drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  nfs_inc_attr_generation_counter () ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 
 int nfs_sillyrename (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 int rpc_wait_for_completion_task (struct rpc_task*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs_rename_enter (struct inode*,struct dentry*,struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  trace_nfs_rename_exit (struct inode*,struct dentry*,struct inode*,struct dentry*,int) ; 

int nfs_rename(struct inode *old_dir, struct dentry *old_dentry,
	       struct inode *new_dir, struct dentry *new_dentry,
	       unsigned int flags)
{
	struct inode *old_inode = d_inode(old_dentry);
	struct inode *new_inode = d_inode(new_dentry);
	struct dentry *dentry = NULL, *rehash = NULL;
	struct rpc_task *task;
	int error = -EBUSY;

	if (flags)
		return -EINVAL;

	dfprintk(VFS, "NFS: rename(%pd2 -> %pd2, ct=%d)\n",
		 old_dentry, new_dentry,
		 d_count(new_dentry));

	trace_nfs_rename_enter(old_dir, old_dentry, new_dir, new_dentry);
	/*
	 * For non-directories, check whether the target is busy and if so,
	 * make a copy of the dentry and then do a silly-rename. If the
	 * silly-rename succeeds, the copied dentry is hashed and becomes
	 * the new target.
	 */
	if (new_inode && !S_ISDIR(new_inode->i_mode)) {
		/*
		 * To prevent any new references to the target during the
		 * rename, we unhash the dentry in advance.
		 */
		if (!d_unhashed(new_dentry)) {
			d_drop(new_dentry);
			rehash = new_dentry;
		}

		if (d_count(new_dentry) > 2) {
			int err;

			/* copy the target dentry's name */
			dentry = d_alloc(new_dentry->d_parent,
					 &new_dentry->d_name);
			if (!dentry)
				goto out;

			/* silly-rename the existing target ... */
			err = nfs_sillyrename(new_dir, new_dentry);
			if (err)
				goto out;

			new_dentry = dentry;
			rehash = NULL;
			new_inode = NULL;
		}
	}

	task = nfs_async_rename(old_dir, new_dir, old_dentry, new_dentry, NULL);
	if (IS_ERR(task)) {
		error = PTR_ERR(task);
		goto out;
	}

	error = rpc_wait_for_completion_task(task);
	if (error != 0) {
		((struct nfs_renamedata *)task->tk_calldata)->cancelled = 1;
		/* Paired with the atomic_dec_and_test() barrier in rpc_do_put_task() */
		smp_wmb();
	} else
		error = task->tk_status;
	rpc_put_task(task);
	/* Ensure the inode attributes are revalidated */
	if (error == 0) {
		spin_lock(&old_inode->i_lock);
		NFS_I(old_inode)->attr_gencount = nfs_inc_attr_generation_counter();
		NFS_I(old_inode)->cache_validity |= NFS_INO_INVALID_CHANGE
			| NFS_INO_INVALID_CTIME
			| NFS_INO_REVAL_FORCED;
		spin_unlock(&old_inode->i_lock);
	}
out:
	if (rehash)
		d_rehash(rehash);
	trace_nfs_rename_exit(old_dir, old_dentry,
			new_dir, new_dentry, error);
	if (!error) {
		if (new_inode != NULL)
			nfs_drop_nlink(new_inode);
		/*
		 * The d_move() should be here instead of in an async RPC completion
		 * handler because we need the proper locks to move the dentry.  If
		 * we're interrupted by a signal, the async RPC completion handler
		 * should mark the directories for revalidation.
		 */
		d_move(old_dentry, new_dentry);
		nfs_set_verifier(old_dentry,
					nfs_save_change_attribute(new_dir));
	} else if (error == -ENOENT)
		nfs_dentry_handle_enoent(old_dentry);

	/* new dentry created? */
	if (dentry)
		dput(dentry);
	return error;
}