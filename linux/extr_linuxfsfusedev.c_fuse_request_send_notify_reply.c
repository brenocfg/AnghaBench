#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int /*<<< orphan*/  unique; } ;
struct TYPE_6__ {TYPE_2__ h; } ;
struct fuse_req {TYPE_3__ in; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct fuse_iqueue {TYPE_1__ waitq; scalar_t__ connected; } ;
struct fuse_conn {struct fuse_iqueue iq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FR_ISREPLY ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_request (struct fuse_iqueue*,struct fuse_req*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_request_send_notify_reply(struct fuse_conn *fc,
					  struct fuse_req *req, u64 unique)
{
	int err = -ENODEV;
	struct fuse_iqueue *fiq = &fc->iq;

	__clear_bit(FR_ISREPLY, &req->flags);
	req->in.h.unique = unique;
	spin_lock(&fiq->waitq.lock);
	if (fiq->connected) {
		queue_request(fiq, req);
		err = 0;
	}
	spin_unlock(&fiq->waitq.lock);

	return err;
}