#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  unique; } ;
struct TYPE_4__ {TYPE_1__ h; } ;
struct fuse_req {TYPE_2__ in; int /*<<< orphan*/  flags; } ;
struct fuse_iqueue {int /*<<< orphan*/  lock; scalar_t__ connected; } ;
struct fuse_conn {struct fuse_iqueue iq; } ;
struct fuse_args {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FR_ISREPLY ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_args_to_req (struct fuse_req*,struct fuse_args*) ; 
 struct fuse_req* fuse_get_req (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  queue_request_and_unlock (struct fuse_iqueue*,struct fuse_req*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_simple_notify_reply(struct fuse_conn *fc,
				    struct fuse_args *args, u64 unique)
{
	struct fuse_req *req;
	struct fuse_iqueue *fiq = &fc->iq;
	int err = 0;

	req = fuse_get_req(fc, false);
	if (IS_ERR(req))
		return PTR_ERR(req);

	__clear_bit(FR_ISREPLY, &req->flags);
	req->in.h.unique = unique;

	fuse_args_to_req(req, args);

	spin_lock(&fiq->lock);
	if (fiq->connected) {
		queue_request_and_unlock(fiq, req);
	} else {
		err = -ENODEV;
		spin_unlock(&fiq->lock);
		fuse_put_request(fc, req);
	}

	return err;
}