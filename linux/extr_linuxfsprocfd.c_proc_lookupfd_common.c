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
struct inode {int dummy; } ;
struct fd_data {unsigned int fd; int /*<<< orphan*/  mode; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
typedef  struct dentry* (* instantiate_t ) (struct dentry*,struct task_struct*,struct fd_data*) ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 unsigned int name_to_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  tid_fd_mode (struct task_struct*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *proc_lookupfd_common(struct inode *dir,
					   struct dentry *dentry,
					   instantiate_t instantiate)
{
	struct task_struct *task = get_proc_task(dir);
	struct fd_data data = {.fd = name_to_int(&dentry->d_name)};
	struct dentry *result = ERR_PTR(-ENOENT);

	if (!task)
		goto out_no_task;
	if (data.fd == ~0U)
		goto out;
	if (!tid_fd_mode(task, data.fd, &data.mode))
		goto out;

	result = instantiate(dentry, task, &data);
out:
	put_task_struct(task);
out_no_task:
	return result;
}