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
struct files_struct {int /*<<< orphan*/  file_lock; } ;
struct file {int dummy; } ;
struct fdtable {unsigned int max_fds; struct file** fd; } ;
struct TYPE_2__ {struct files_struct* files; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __put_unused_fd (struct files_struct*,unsigned int) ; 
 TYPE_1__* current ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int filp_close (struct file*,struct files_struct*) ; 
 int /*<<< orphan*/  get_file (struct file*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __close_fd_get_file(unsigned int fd, struct file **res)
{
	struct files_struct *files = current->files;
	struct file *file;
	struct fdtable *fdt;

	spin_lock(&files->file_lock);
	fdt = files_fdtable(files);
	if (fd >= fdt->max_fds)
		goto out_unlock;
	file = fdt->fd[fd];
	if (!file)
		goto out_unlock;
	rcu_assign_pointer(fdt->fd[fd], NULL);
	__put_unused_fd(files, fd);
	spin_unlock(&files->file_lock);
	get_file(file);
	*res = file;
	return filp_close(file, files);

out_unlock:
	spin_unlock(&files->file_lock);
	*res = NULL;
	return -ENOENT;
}