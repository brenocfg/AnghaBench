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
struct pid_entry {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct dir_context {unsigned int pos; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct task_struct* get_proc_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fill_cache (struct file*,struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,struct pid_entry const*) ; 
 int /*<<< orphan*/  proc_pident_instantiate ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int proc_pident_readdir(struct file *file, struct dir_context *ctx,
		const struct pid_entry *ents, unsigned int nents)
{
	struct task_struct *task = get_proc_task(file_inode(file));
	const struct pid_entry *p;

	if (!task)
		return -ENOENT;

	if (!dir_emit_dots(file, ctx))
		goto out;

	if (ctx->pos >= nents + 2)
		goto out;

	for (p = ents + (ctx->pos - 2); p < ents + nents; p++) {
		if (!proc_fill_cache(file, ctx, p->name, p->len,
				proc_pident_instantiate, task, p))
			break;
		ctx->pos++;
	}
out:
	put_task_struct(task);
	return 0;
}