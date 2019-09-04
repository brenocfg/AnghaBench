#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  unique; } ;
struct TYPE_9__ {TYPE_3__ h; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; } ;
struct TYPE_7__ {TYPE_1__ h; } ;
struct fuse_req {TYPE_4__ in; TYPE_2__ out; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct fuse_iqueue {TYPE_5__ waitq; int /*<<< orphan*/  connected; } ;
struct fuse_conn {struct fuse_iqueue iq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  __fuse_get_request (struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_get_unique (struct fuse_iqueue*) ; 
 int /*<<< orphan*/  queue_request (struct fuse_iqueue*,struct fuse_req*) ; 
 int /*<<< orphan*/  request_wait_answer (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __fuse_request_send(struct fuse_conn *fc, struct fuse_req *req)
{
	struct fuse_iqueue *fiq = &fc->iq;

	BUG_ON(test_bit(FR_BACKGROUND, &req->flags));
	spin_lock(&fiq->waitq.lock);
	if (!fiq->connected) {
		spin_unlock(&fiq->waitq.lock);
		req->out.h.error = -ENOTCONN;
	} else {
		req->in.h.unique = fuse_get_unique(fiq);
		queue_request(fiq, req);
		/* acquire extra reference, since request is still needed
		   after request_end() */
		__fuse_get_request(req);
		spin_unlock(&fiq->waitq.lock);

		request_wait_answer(fc, req);
		/* Pairs with smp_wmb() in request_end() */
		smp_rmb();
	}
}