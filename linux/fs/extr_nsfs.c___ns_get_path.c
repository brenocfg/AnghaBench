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
struct vfsmount {int /*<<< orphan*/  mnt_sb; } ;
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct ns_common {int /*<<< orphan*/  stashed; TYPE_1__* ops; int /*<<< orphan*/  inum; } ;
struct inode {int i_mode; struct ns_common* i_private; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct dentry {void* d_fsdata; int /*<<< orphan*/  d_lockref; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put ) (struct ns_common*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFREG ; 
 int /*<<< orphan*/  S_IMMUTABLE ; 
 int S_IRUGO ; 
 unsigned long atomic_long_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct dentry* d_alloc_anon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lockref_get_not_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 struct inode* new_inode_pseudo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_file_operations ; 
 struct vfsmount* nsfs_mnt ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct ns_common*) ; 
 int /*<<< orphan*/  stub2 (struct ns_common*) ; 

__attribute__((used)) static void *__ns_get_path(struct path *path, struct ns_common *ns)
{
	struct vfsmount *mnt = nsfs_mnt;
	struct dentry *dentry;
	struct inode *inode;
	unsigned long d;

	rcu_read_lock();
	d = atomic_long_read(&ns->stashed);
	if (!d)
		goto slow;
	dentry = (struct dentry *)d;
	if (!lockref_get_not_dead(&dentry->d_lockref))
		goto slow;
	rcu_read_unlock();
	ns->ops->put(ns);
got_it:
	path->mnt = mntget(mnt);
	path->dentry = dentry;
	return NULL;
slow:
	rcu_read_unlock();
	inode = new_inode_pseudo(mnt->mnt_sb);
	if (!inode) {
		ns->ops->put(ns);
		return ERR_PTR(-ENOMEM);
	}
	inode->i_ino = ns->inum;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_flags |= S_IMMUTABLE;
	inode->i_mode = S_IFREG | S_IRUGO;
	inode->i_fop = &ns_file_operations;
	inode->i_private = ns;

	dentry = d_alloc_anon(mnt->mnt_sb);
	if (!dentry) {
		iput(inode);
		return ERR_PTR(-ENOMEM);
	}
	d_instantiate(dentry, inode);
	dentry->d_fsdata = (void *)ns->ops;
	d = atomic_long_cmpxchg(&ns->stashed, 0, (unsigned long)dentry);
	if (d) {
		d_delete(dentry);	/* make sure ->d_prune() does nothing */
		dput(dentry);
		cpu_relax();
		return ERR_PTR(-EAGAIN);
	}
	goto got_it;
}