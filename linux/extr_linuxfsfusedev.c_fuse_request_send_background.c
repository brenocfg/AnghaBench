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
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
struct TYPE_4__ {TYPE_1__ h; } ;
struct fuse_req {int /*<<< orphan*/  (* end ) (struct fuse_conn*,struct fuse_req*) ;TYPE_2__ out; } ;
struct fuse_conn {int /*<<< orphan*/  lock; scalar_t__ connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send_background_locked (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fuse_conn*,struct fuse_req*) ; 

void fuse_request_send_background(struct fuse_conn *fc, struct fuse_req *req)
{
	BUG_ON(!req->end);
	spin_lock(&fc->lock);
	if (fc->connected) {
		fuse_request_send_background_locked(fc, req);
		spin_unlock(&fc->lock);
	} else {
		spin_unlock(&fc->lock);
		req->out.h.error = -ENOTCONN;
		req->end(fc, req);
		fuse_put_request(fc, req);
	}
}