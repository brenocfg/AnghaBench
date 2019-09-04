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
struct kioctx {int /*<<< orphan*/  reqs; } ;
struct aio_kiocb {struct kioctx* ki_ctx; int /*<<< orphan*/  ki_refcnt; int /*<<< orphan*/  ki_list; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  get_reqs_available (struct kioctx*) ; 
 int /*<<< orphan*/  kiocb_cachep ; 
 struct aio_kiocb* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_reqs_available (struct kioctx*,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_refill_reqs_available (struct kioctx*) ; 

__attribute__((used)) static inline struct aio_kiocb *aio_get_req(struct kioctx *ctx)
{
	struct aio_kiocb *req;

	if (!get_reqs_available(ctx)) {
		user_refill_reqs_available(ctx);
		if (!get_reqs_available(ctx))
			return NULL;
	}

	req = kmem_cache_alloc(kiocb_cachep, GFP_KERNEL|__GFP_ZERO);
	if (unlikely(!req))
		goto out_put;

	percpu_ref_get(&ctx->reqs);
	INIT_LIST_HEAD(&req->ki_list);
	refcount_set(&req->ki_refcnt, 0);
	req->ki_ctx = ctx;
	return req;
out_put:
	put_reqs_available(ctx, 1);
	return NULL;
}