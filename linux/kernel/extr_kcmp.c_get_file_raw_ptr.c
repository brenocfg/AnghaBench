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
struct task_struct {scalar_t__ files; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct file* fcheck_files (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static struct file *
get_file_raw_ptr(struct task_struct *task, unsigned int idx)
{
	struct file *file = NULL;

	task_lock(task);
	rcu_read_lock();

	if (task->files)
		file = fcheck_files(task->files, idx);

	rcu_read_unlock();
	task_unlock(task);

	return file;
}