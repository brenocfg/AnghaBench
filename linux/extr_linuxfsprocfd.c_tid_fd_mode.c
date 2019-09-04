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
struct task_struct {int dummy; } ;
struct files_struct {int dummy; } ;
struct file {int /*<<< orphan*/  f_mode; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 struct file* fcheck_files (struct files_struct*,unsigned int) ; 
 struct files_struct* get_files_struct (struct task_struct*) ; 
 int /*<<< orphan*/  put_files_struct (struct files_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool tid_fd_mode(struct task_struct *task, unsigned fd, fmode_t *mode)
{
	struct files_struct *files = get_files_struct(task);
	struct file *file;

	if (!files)
		return false;

	rcu_read_lock();
	file = fcheck_files(files, fd);
	if (file)
		*mode = file->f_mode;
	rcu_read_unlock();
	put_files_struct(files);
	return !!file;
}