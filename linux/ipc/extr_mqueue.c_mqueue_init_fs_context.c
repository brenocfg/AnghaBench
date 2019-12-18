#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mqueue_fs_context {TYPE_2__* ipc_ns; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct mqueue_fs_context* fs_private; int /*<<< orphan*/  user_ns; } ;
struct TYPE_6__ {TYPE_1__* nsproxy; } ;
struct TYPE_5__ {int /*<<< orphan*/  user_ns; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipc_ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__* current ; 
 TYPE_2__* get_ipc_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_user_ns (int /*<<< orphan*/ ) ; 
 struct mqueue_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqueue_fs_context_ops ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mqueue_init_fs_context(struct fs_context *fc)
{
	struct mqueue_fs_context *ctx;

	ctx = kzalloc(sizeof(struct mqueue_fs_context), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->ipc_ns = get_ipc_ns(current->nsproxy->ipc_ns);
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->ipc_ns->user_ns);
	fc->fs_private = ctx;
	fc->ops = &mqueue_fs_context_ops;
	return 0;
}