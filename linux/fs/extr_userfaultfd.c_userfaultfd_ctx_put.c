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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct userfaultfd_ctx {int /*<<< orphan*/  mm; TYPE_1__ fd_wqh; TYPE_1__ event_wqh; TYPE_1__ fault_wqh; TYPE_1__ fault_pending_wqh; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct userfaultfd_ctx*) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userfaultfd_ctx_cachep ; 
 int /*<<< orphan*/  waitqueue_active (TYPE_1__*) ; 

__attribute__((used)) static void userfaultfd_ctx_put(struct userfaultfd_ctx *ctx)
{
	if (refcount_dec_and_test(&ctx->refcount)) {
		VM_BUG_ON(spin_is_locked(&ctx->fault_pending_wqh.lock));
		VM_BUG_ON(waitqueue_active(&ctx->fault_pending_wqh));
		VM_BUG_ON(spin_is_locked(&ctx->fault_wqh.lock));
		VM_BUG_ON(waitqueue_active(&ctx->fault_wqh));
		VM_BUG_ON(spin_is_locked(&ctx->event_wqh.lock));
		VM_BUG_ON(waitqueue_active(&ctx->event_wqh));
		VM_BUG_ON(spin_is_locked(&ctx->fd_wqh.lock));
		VM_BUG_ON(waitqueue_active(&ctx->fd_wqh));
		mmdrop(ctx->mm);
		kmem_cache_free(userfaultfd_ctx_cachep, ctx);
	}
}