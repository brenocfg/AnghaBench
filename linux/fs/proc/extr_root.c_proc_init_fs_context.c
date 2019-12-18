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
struct proc_fs_context {TYPE_1__* pid_ns; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct proc_fs_context* fs_private; int /*<<< orphan*/  user_ns; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* get_pid_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_user_ns (int /*<<< orphan*/ ) ; 
 struct proc_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fs_context_ops ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_init_fs_context(struct fs_context *fc)
{
	struct proc_fs_context *ctx;

	ctx = kzalloc(sizeof(struct proc_fs_context), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->pid_ns = get_pid_ns(task_active_pid_ns(current));
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->pid_ns->user_ns);
	fc->fs_private = ctx;
	fc->ops = &proc_fs_context_ops;
	return 0;
}