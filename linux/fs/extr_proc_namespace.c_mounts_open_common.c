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
struct task_struct {int /*<<< orphan*/  fs; struct nsproxy* nsproxy; } ;
struct seq_file {struct proc_mounts* private; int /*<<< orphan*/  poll_event; } ;
struct path {int dummy; } ;
struct proc_mounts {int (* show ) (struct seq_file*,struct vfsmount*) ;unsigned long long cached_event; struct path root; struct mnt_namespace* ns; } ;
struct nsproxy {struct mnt_namespace* mnt_ns; } ;
struct mnt_namespace {int /*<<< orphan*/  event; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  get_fs_root (int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  get_mnt_ns (struct mnt_namespace*) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  mounts_op ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_mnt_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int seq_open_private (struct file*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static int mounts_open_common(struct inode *inode, struct file *file,
			      int (*show)(struct seq_file *, struct vfsmount *))
{
	struct task_struct *task = get_proc_task(inode);
	struct nsproxy *nsp;
	struct mnt_namespace *ns = NULL;
	struct path root;
	struct proc_mounts *p;
	struct seq_file *m;
	int ret = -EINVAL;

	if (!task)
		goto err;

	task_lock(task);
	nsp = task->nsproxy;
	if (!nsp || !nsp->mnt_ns) {
		task_unlock(task);
		put_task_struct(task);
		goto err;
	}
	ns = nsp->mnt_ns;
	get_mnt_ns(ns);
	if (!task->fs) {
		task_unlock(task);
		put_task_struct(task);
		ret = -ENOENT;
		goto err_put_ns;
	}
	get_fs_root(task->fs, &root);
	task_unlock(task);
	put_task_struct(task);

	ret = seq_open_private(file, &mounts_op, sizeof(struct proc_mounts));
	if (ret)
		goto err_put_path;

	m = file->private_data;
	m->poll_event = ns->event;

	p = m->private;
	p->ns = ns;
	p->root = root;
	p->show = show;
	p->cached_event = ~0ULL;

	return 0;

 err_put_path:
	path_put(&root);
 err_put_ns:
	put_mnt_ns(ns);
 err:
	return ret;
}