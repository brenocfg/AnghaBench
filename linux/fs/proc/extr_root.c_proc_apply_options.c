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
struct user_namespace {int dummy; } ;
struct super_block {int dummy; } ;
struct proc_fs_context {int mask; int /*<<< orphan*/  hidepid; int /*<<< orphan*/  gid; } ;
struct pid_namespace {int /*<<< orphan*/  hide_pid; int /*<<< orphan*/  pid_gid; } ;
struct fs_context {struct proc_fs_context* fs_private; } ;

/* Variables and functions */
 int Opt_gid ; 
 int Opt_hidepid ; 
 int /*<<< orphan*/  make_kgid (struct user_namespace*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proc_apply_options(struct super_block *s,
			       struct fs_context *fc,
			       struct pid_namespace *pid_ns,
			       struct user_namespace *user_ns)
{
	struct proc_fs_context *ctx = fc->fs_private;

	if (ctx->mask & (1 << Opt_gid))
		pid_ns->pid_gid = make_kgid(user_ns, ctx->gid);
	if (ctx->mask & (1 << Opt_hidepid))
		pid_ns->hide_pid = ctx->hidepid;
}