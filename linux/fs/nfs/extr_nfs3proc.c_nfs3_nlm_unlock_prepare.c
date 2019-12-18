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
struct rpc_task {int dummy; } ;
struct nfs_lock_context {TYPE_1__* open_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CONTEXT_UNLOCK ; 
 int nfs_async_iocounter_wait (struct rpc_task*,struct nfs_lock_context*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs3_nlm_unlock_prepare(struct rpc_task *task, void *data)
{
	struct nfs_lock_context *l_ctx = data;
	if (l_ctx && test_bit(NFS_CONTEXT_UNLOCK, &l_ctx->open_context->flags))
		return nfs_async_iocounter_wait(task, l_ctx);
	return false;

}