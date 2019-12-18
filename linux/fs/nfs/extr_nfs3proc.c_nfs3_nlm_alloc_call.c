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
struct nfs_lock_context {TYPE_1__* open_context; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CONTEXT_UNLOCK ; 
 int /*<<< orphan*/  get_nfs_open_context (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_get_lock_context (TYPE_1__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs3_nlm_alloc_call(void *data)
{
	struct nfs_lock_context *l_ctx = data;
	if (l_ctx && test_bit(NFS_CONTEXT_UNLOCK, &l_ctx->open_context->flags)) {
		get_nfs_open_context(l_ctx->open_context);
		nfs_get_lock_context(l_ctx->open_context);
	}
}