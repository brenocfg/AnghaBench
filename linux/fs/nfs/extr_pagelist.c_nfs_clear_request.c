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
struct page {int dummy; } ;
struct nfs_page {struct nfs_lock_context* wb_lock_context; struct page* wb_page; } ;
struct nfs_open_context {int /*<<< orphan*/  dentry; int /*<<< orphan*/  flags; } ;
struct nfs_lock_context {struct nfs_open_context* open_context; int /*<<< orphan*/  io_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  uoc_rpcwaitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CONTEXT_UNLOCK ; 
 TYPE_1__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_put_lock_context (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rpc_wake_up (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_clear_request(struct nfs_page *req)
{
	struct page *page = req->wb_page;
	struct nfs_lock_context *l_ctx = req->wb_lock_context;
	struct nfs_open_context *ctx;

	if (page != NULL) {
		put_page(page);
		req->wb_page = NULL;
	}
	if (l_ctx != NULL) {
		if (atomic_dec_and_test(&l_ctx->io_count)) {
			wake_up_var(&l_ctx->io_count);
			ctx = l_ctx->open_context;
			if (test_bit(NFS_CONTEXT_UNLOCK, &ctx->flags))
				rpc_wake_up(&NFS_SERVER(d_inode(ctx->dentry))->uoc_rpcwaitq);
		}
		nfs_put_lock_context(l_ctx);
		req->wb_lock_context = NULL;
	}
}