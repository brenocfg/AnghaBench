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
struct aio_kiocb {int /*<<< orphan*/ * ki_eventfd; int /*<<< orphan*/  ki_refcnt; int /*<<< orphan*/  ki_list; struct kioctx* ki_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_reqs_available (struct kioctx*) ; 
 int /*<<< orphan*/  kiocb_cachep ; 
 struct aio_kiocb* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct aio_kiocb*) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct aio_kiocb *aio_get_req(struct kioctx *ctx)
{
	struct aio_kiocb *req;

	req = kmem_cache_alloc(kiocb_cachep, GFP_KERNEL);
	if (unlikely(!req))
		return NULL;

	if (unlikely(!get_reqs_available(ctx))) {
		kmem_cache_free(kiocb_cachep, req);
		return NULL;
	}

	percpu_ref_get(&ctx->reqs);
	req->ki_ctx = ctx;
	INIT_LIST_HEAD(&req->ki_list);
	refcount_set(&req->ki_refcnt, 2);
	req->ki_eventfd = NULL;
	return req;
}