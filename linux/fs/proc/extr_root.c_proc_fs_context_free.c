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
struct proc_fs_context {int /*<<< orphan*/  pid_ns; } ;
struct fs_context {struct proc_fs_context* fs_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct proc_fs_context*) ; 
 int /*<<< orphan*/  put_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proc_fs_context_free(struct fs_context *fc)
{
	struct proc_fs_context *ctx = fc->fs_private;

	put_pid_ns(ctx->pid_ns);
	kfree(ctx);
}