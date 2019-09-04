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
struct fuse_req {int /*<<< orphan*/  (* end ) (struct fuse_conn*,struct fuse_req*) ;int /*<<< orphan*/  waitq; int /*<<< orphan*/  flags; int /*<<< orphan*/  intr_entry; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct fuse_iqueue {TYPE_1__ waitq; } ;
struct fuse_conn {scalar_t__ num_background; scalar_t__ max_background; scalar_t__ congestion_threshold; int /*<<< orphan*/  lock; int /*<<< orphan*/  active_background; TYPE_2__* sb; int /*<<< orphan*/  blocked_waitq; scalar_t__ blocked; struct fuse_iqueue iq; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int /*<<< orphan*/  BLK_RW_SYNC ; 
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  FR_FINISHED ; 
 int /*<<< orphan*/  FR_PENDING ; 
 int /*<<< orphan*/  FR_SENT ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  clear_bdi_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_bg_queue (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fuse_conn*,struct fuse_req*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void request_end(struct fuse_conn *fc, struct fuse_req *req)
{
	struct fuse_iqueue *fiq = &fc->iq;

	if (test_and_set_bit(FR_FINISHED, &req->flags))
		goto put_request;

	spin_lock(&fiq->waitq.lock);
	list_del_init(&req->intr_entry);
	spin_unlock(&fiq->waitq.lock);
	WARN_ON(test_bit(FR_PENDING, &req->flags));
	WARN_ON(test_bit(FR_SENT, &req->flags));
	if (test_bit(FR_BACKGROUND, &req->flags)) {
		spin_lock(&fc->lock);
		clear_bit(FR_BACKGROUND, &req->flags);
		if (fc->num_background == fc->max_background) {
			fc->blocked = 0;
			wake_up(&fc->blocked_waitq);
		} else if (!fc->blocked) {
			/*
			 * Wake up next waiter, if any.  It's okay to use
			 * waitqueue_active(), as we've already synced up
			 * fc->blocked with waiters with the wake_up() call
			 * above.
			 */
			if (waitqueue_active(&fc->blocked_waitq))
				wake_up(&fc->blocked_waitq);
		}

		if (fc->num_background == fc->congestion_threshold && fc->sb) {
			clear_bdi_congested(fc->sb->s_bdi, BLK_RW_SYNC);
			clear_bdi_congested(fc->sb->s_bdi, BLK_RW_ASYNC);
		}
		fc->num_background--;
		fc->active_background--;
		flush_bg_queue(fc);
		spin_unlock(&fc->lock);
	}
	wake_up(&req->waitq);
	if (req->end)
		req->end(fc, req);
put_request:
	fuse_put_request(fc, req);
}