#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tag; } ;
struct TYPE_5__ {int /*<<< orphan*/  refcount; } ;
struct p9_req_t {TYPE_2__ rc; TYPE_2__ tc; TYPE_1__ refcount; int /*<<< orphan*/  req_list; int /*<<< orphan*/  wq; int /*<<< orphan*/  status; scalar_t__ t_err; } ;
struct p9_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  reqs; int /*<<< orphan*/  msize; } ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct p9_req_t* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ P9_NOTAG ; 
 scalar_t__ P9_TVERSION ; 
 int /*<<< orphan*/  REQ_STATUS_ALLOC ; 
 int idr_alloc (int /*<<< orphan*/ *,struct p9_req_t*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct p9_req_t* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct p9_req_t*) ; 
 int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  p9_fcall_fini (TYPE_2__*) ; 
 scalar_t__ p9_fcall_init (struct p9_client*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  p9_req_cache ; 
 int /*<<< orphan*/  p9pdu_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct p9_req_t *
p9_tag_alloc(struct p9_client *c, int8_t type, unsigned int max_size)
{
	struct p9_req_t *req = kmem_cache_alloc(p9_req_cache, GFP_NOFS);
	int alloc_msize = min(c->msize, max_size);
	int tag;

	if (!req)
		return ERR_PTR(-ENOMEM);

	if (p9_fcall_init(c, &req->tc, alloc_msize))
		goto free_req;
	if (p9_fcall_init(c, &req->rc, alloc_msize))
		goto free;

	p9pdu_reset(&req->tc);
	p9pdu_reset(&req->rc);
	req->t_err = 0;
	req->status = REQ_STATUS_ALLOC;
	init_waitqueue_head(&req->wq);
	INIT_LIST_HEAD(&req->req_list);

	idr_preload(GFP_NOFS);
	spin_lock_irq(&c->lock);
	if (type == P9_TVERSION)
		tag = idr_alloc(&c->reqs, req, P9_NOTAG, P9_NOTAG + 1,
				GFP_NOWAIT);
	else
		tag = idr_alloc(&c->reqs, req, 0, P9_NOTAG, GFP_NOWAIT);
	req->tc.tag = tag;
	spin_unlock_irq(&c->lock);
	idr_preload_end();
	if (tag < 0)
		goto free;

	/* Init ref to two because in the general case there is one ref
	 * that is put asynchronously by a writer thread, one ref
	 * temporarily given by p9_tag_lookup and put by p9_client_cb
	 * in the recv thread, and one ref put by p9_tag_remove in the
	 * main thread. The only exception is virtio that does not use
	 * p9_tag_lookup but does not have a writer thread either
	 * (the write happens synchronously in the request/zc_request
	 * callback), so p9_client_cb eats the second ref there
	 * as the pointer is duplicated directly by virtqueue_add_sgs()
	 */
	refcount_set(&req->refcount.refcount, 2);

	return req;

free:
	p9_fcall_fini(&req->tc);
	p9_fcall_fini(&req->rc);
free_req:
	kmem_cache_free(p9_req_cache, req);
	return ERR_PTR(-ENOMEM);
}