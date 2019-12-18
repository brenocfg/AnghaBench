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
struct path {int dummy; } ;
struct files_struct {int /*<<< orphan*/  file_lock; } ;
struct file {struct path f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct file* fcheck_files (struct files_struct*,unsigned int) ; 
 struct files_struct* get_files_struct (struct task_struct*) ; 
 struct task_struct* get_proc_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 unsigned int proc_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_files_struct (struct files_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proc_fd_link(struct dentry *dentry, struct path *path)
{
	struct files_struct *files = NULL;
	struct task_struct *task;
	int ret = -ENOENT;

	task = get_proc_task(d_inode(dentry));
	if (task) {
		files = get_files_struct(task);
		put_task_struct(task);
	}

	if (files) {
		unsigned int fd = proc_fd(d_inode(dentry));
		struct file *fd_file;

		spin_lock(&files->file_lock);
		fd_file = fcheck_files(files, fd);
		if (fd_file) {
			*path = fd_file->f_path;
			path_get(&fd_file->f_path);
			ret = 0;
		}
		spin_unlock(&files->file_lock);
		put_files_struct(files);
	}

	return ret;
}