#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  unique; } ;
struct TYPE_8__ {TYPE_3__ h; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct TYPE_6__ {TYPE_1__ h; } ;
struct fuse_req {TYPE_4__ in; TYPE_2__ out; int /*<<< orphan*/  flags; } ;
struct fuse_iqueue {int /*<<< orphan*/  lock; int /*<<< orphan*/  connected; } ;
struct fuse_conn {struct fuse_iqueue iq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  __fuse_get_request (struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_get_unique (struct fuse_iqueue*) ; 
 int /*<<< orphan*/  queue_request_and_unlock (struct fuse_iqueue*,struct fuse_req*) ; 
 int /*<<< orphan*/  request_wait_answer (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __fuse_request_send(struct fuse_conn *fc, struct fuse_req *req)
{
	struct fuse_iqueue *fiq = &fc->iq;

	BUG_ON(test_bit(FR_BACKGROUND, &req->flags));
	spin_lock(&fiq->lock);
	if (!fiq->connected) {
		spin_unlock(&fiq->lock);
		req->out.h.error = -ENOTCONN;
	} else {
		req->in.h.unique = fuse_get_unique(fiq);
		/* acquire extra reference, since request is still needed
		   after fuse_request_end() */
		__fuse_get_request(req);
		queue_request_and_unlock(fiq, req);

		request_wait_answer(fc, req);
		/* Pairs with smp_wmb() in fuse_request_end() */
		smp_rmb();
	}
}