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
struct proc_ns_operations {int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct dir_context {int pos; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct proc_ns_operations**) ; 
 int ENOENT ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct task_struct* get_proc_task (int /*<<< orphan*/ ) ; 
 struct proc_ns_operations** ns_entries ; 
 int /*<<< orphan*/  proc_fill_cache (struct file*,struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,struct proc_ns_operations const*) ; 
 int /*<<< orphan*/  proc_ns_instantiate ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_ns_dir_readdir(struct file *file, struct dir_context *ctx)
{
	struct task_struct *task = get_proc_task(file_inode(file));
	const struct proc_ns_operations **entry, **last;

	if (!task)
		return -ENOENT;

	if (!dir_emit_dots(file, ctx))
		goto out;
	if (ctx->pos >= 2 + ARRAY_SIZE(ns_entries))
		goto out;
	entry = ns_entries + (ctx->pos - 2);
	last = &ns_entries[ARRAY_SIZE(ns_entries) - 1];
	while (entry <= last) {
		const struct proc_ns_operations *ops = *entry;
		if (!proc_fill_cache(file, ctx, ops->name, strlen(ops->name),
				     proc_ns_instantiate, task, ops))
			break;
		ctx->pos++;
		entry++;
	}
out:
	put_task_struct(task);
	return 0;
}