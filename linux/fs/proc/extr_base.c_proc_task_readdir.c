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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ f_version; } ;
struct dir_context {scalar_t__ pos; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 struct inode* file_inode (struct file*) ; 
 struct task_struct* first_tid (int /*<<< orphan*/ ,int,scalar_t__,struct pid_namespace*) ; 
 struct task_struct* next_tid (struct task_struct*) ; 
 int /*<<< orphan*/  proc_fill_cache (struct file*,struct dir_context*,char*,unsigned int,int /*<<< orphan*/ ,struct task_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ proc_inode_is_dead (struct inode*) ; 
 int /*<<< orphan*/  proc_pid (struct inode*) ; 
 struct pid_namespace* proc_pid_ns (struct inode*) ; 
 int /*<<< orphan*/  proc_task_instantiate ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 unsigned int snprintf (char*,int,char*,int) ; 
 int task_pid_nr_ns (struct task_struct*,struct pid_namespace*) ; 

__attribute__((used)) static int proc_task_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	struct task_struct *task;
	struct pid_namespace *ns;
	int tid;

	if (proc_inode_is_dead(inode))
		return -ENOENT;

	if (!dir_emit_dots(file, ctx))
		return 0;

	/* f_version caches the tgid value that the last readdir call couldn't
	 * return. lseek aka telldir automagically resets f_version to 0.
	 */
	ns = proc_pid_ns(inode);
	tid = (int)file->f_version;
	file->f_version = 0;
	for (task = first_tid(proc_pid(inode), tid, ctx->pos - 2, ns);
	     task;
	     task = next_tid(task), ctx->pos++) {
		char name[10 + 1];
		unsigned int len;
		tid = task_pid_nr_ns(task, ns);
		len = snprintf(name, sizeof(name), "%u", tid);
		if (!proc_fill_cache(file, ctx, name, len,
				proc_task_instantiate, task, NULL)) {
			/* returning this tgid failed, save it as the first
			 * pid for the next readir call */
			file->f_version = (u64)tid;
			put_task_struct(task);
			break;
		}
	}

	return 0;
}