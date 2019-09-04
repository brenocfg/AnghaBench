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
struct nfs_open_context {int /*<<< orphan*/  flags; } ;
struct nfs_lock_context {struct nfs_open_context* open_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CONTEXT_UNLOCK ; 
 int /*<<< orphan*/  nfs_put_lock_context (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  put_nfs_open_context (struct nfs_open_context*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs3_nlm_release_call(void *data)
{
	struct nfs_lock_context *l_ctx = data;
	struct nfs_open_context *ctx;
	if (l_ctx && test_bit(NFS_CONTEXT_UNLOCK, &l_ctx->open_context->flags)) {
		ctx = l_ctx->open_context;
		nfs_put_lock_context(l_ctx);
		put_nfs_open_context(ctx);
	}
}