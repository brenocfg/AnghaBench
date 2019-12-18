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
struct vfsmount {scalar_t__ user_ns; struct proc_fs_context* fs_private; } ;
struct proc_fs_context {struct pid_namespace* pid_ns; } ;
struct pid_namespace {scalar_t__ user_ns; struct vfsmount* proc_mnt; } ;
struct fs_context {scalar_t__ user_ns; struct proc_fs_context* fs_private; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 int /*<<< orphan*/  SB_KERNMOUNT ; 
 struct vfsmount* fc_mount (struct vfsmount*) ; 
 struct vfsmount* fs_context_for_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 scalar_t__ get_user_ns (scalar_t__) ; 
 int /*<<< orphan*/  proc_fs_type ; 
 int /*<<< orphan*/  put_fs_context (struct vfsmount*) ; 
 int /*<<< orphan*/  put_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  put_user_ns (scalar_t__) ; 

int pid_ns_prepare_proc(struct pid_namespace *ns)
{
	struct proc_fs_context *ctx;
	struct fs_context *fc;
	struct vfsmount *mnt;

	fc = fs_context_for_mount(&proc_fs_type, SB_KERNMOUNT);
	if (IS_ERR(fc))
		return PTR_ERR(fc);

	if (fc->user_ns != ns->user_ns) {
		put_user_ns(fc->user_ns);
		fc->user_ns = get_user_ns(ns->user_ns);
	}

	ctx = fc->fs_private;
	if (ctx->pid_ns != ns) {
		put_pid_ns(ctx->pid_ns);
		get_pid_ns(ns);
		ctx->pid_ns = ns;
	}

	mnt = fc_mount(fc);
	put_fs_context(fc);
	if (IS_ERR(mnt))
		return PTR_ERR(mnt);

	ns->proc_mnt = mnt;
	return 0;
}