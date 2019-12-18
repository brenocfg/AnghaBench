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
struct file {struct path f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct task_struct* get_proc_task (int /*<<< orphan*/ ) ; 
 struct file* get_task_exe_file (struct task_struct*) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int proc_exe_link(struct dentry *dentry, struct path *exe_path)
{
	struct task_struct *task;
	struct file *exe_file;

	task = get_proc_task(d_inode(dentry));
	if (!task)
		return -ENOENT;
	exe_file = get_task_exe_file(task);
	put_task_struct(task);
	if (exe_file) {
		*exe_path = exe_file->f_path;
		path_get(&exe_file->f_path);
		fput(exe_file);
		return 0;
	} else
		return -ENOENT;
}