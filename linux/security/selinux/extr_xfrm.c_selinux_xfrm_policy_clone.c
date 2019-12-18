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
struct xfrm_sec_ctx {scalar_t__ ctx_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct xfrm_sec_ctx* kmemdup (struct xfrm_sec_ctx*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_xfrm_refcount ; 

int selinux_xfrm_policy_clone(struct xfrm_sec_ctx *old_ctx,
			      struct xfrm_sec_ctx **new_ctxp)
{
	struct xfrm_sec_ctx *new_ctx;

	if (!old_ctx)
		return 0;

	new_ctx = kmemdup(old_ctx, sizeof(*old_ctx) + old_ctx->ctx_len,
			  GFP_ATOMIC);
	if (!new_ctx)
		return -ENOMEM;
	atomic_inc(&selinux_xfrm_refcount);
	*new_ctxp = new_ctx;

	return 0;
}