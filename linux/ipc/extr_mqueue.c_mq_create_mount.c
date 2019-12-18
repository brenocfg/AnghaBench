#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct mqueue_fs_context {TYPE_1__* ipc_ns; } ;
struct ipc_namespace {int dummy; } ;
struct fs_context {int /*<<< orphan*/  user_ns; struct mqueue_fs_context* fs_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 struct vfsmount* ERR_CAST (struct fs_context*) ; 
 scalar_t__ IS_ERR (struct fs_context*) ; 
 int /*<<< orphan*/  SB_KERNMOUNT ; 
 struct vfsmount* fc_mount (struct fs_context*) ; 
 struct fs_context* fs_context_for_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_ipc_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  get_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqueue_fs_type ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  put_ipc_ns (TYPE_1__*) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vfsmount *mq_create_mount(struct ipc_namespace *ns)
{
	struct mqueue_fs_context *ctx;
	struct fs_context *fc;
	struct vfsmount *mnt;

	fc = fs_context_for_mount(&mqueue_fs_type, SB_KERNMOUNT);
	if (IS_ERR(fc))
		return ERR_CAST(fc);

	ctx = fc->fs_private;
	put_ipc_ns(ctx->ipc_ns);
	ctx->ipc_ns = get_ipc_ns(ns);
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->ipc_ns->user_ns);

	mnt = fc_mount(fc);
	put_fs_context(fc);
	return mnt;
}