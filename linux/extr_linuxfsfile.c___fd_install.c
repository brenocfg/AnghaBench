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
struct files_struct {int /*<<< orphan*/  fdt; int /*<<< orphan*/  file_lock; int /*<<< orphan*/  resize_in_progress; } ;
struct file {int dummy; } ;
struct fdtable {int /*<<< orphan*/ ** fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct file*) ; 
 struct fdtable* rcu_dereference_sched (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_sched () ; 
 int /*<<< orphan*/  rcu_read_unlock_sched () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void __fd_install(struct files_struct *files, unsigned int fd,
		struct file *file)
{
	struct fdtable *fdt;

	rcu_read_lock_sched();

	if (unlikely(files->resize_in_progress)) {
		rcu_read_unlock_sched();
		spin_lock(&files->file_lock);
		fdt = files_fdtable(files);
		BUG_ON(fdt->fd[fd] != NULL);
		rcu_assign_pointer(fdt->fd[fd], file);
		spin_unlock(&files->file_lock);
		return;
	}
	/* coupled with smp_wmb() in expand_fdtable() */
	smp_rmb();
	fdt = rcu_dereference_sched(files->fdt);
	BUG_ON(fdt->fd[fd] != NULL);
	rcu_assign_pointer(fdt->fd[fd], file);
	rcu_read_unlock_sched();
}