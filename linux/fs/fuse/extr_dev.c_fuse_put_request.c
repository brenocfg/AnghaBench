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
struct fuse_req {int /*<<< orphan*/  flags; int /*<<< orphan*/  count; } ;
struct fuse_conn {int /*<<< orphan*/  bg_lock; int /*<<< orphan*/  blocked_waitq; int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  FR_WAITING ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_drop_waiting (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_request_free (struct fuse_req*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_put_request(struct fuse_conn *fc, struct fuse_req *req)
{
	if (refcount_dec_and_test(&req->count)) {
		if (test_bit(FR_BACKGROUND, &req->flags)) {
			/*
			 * We get here in the unlikely case that a background
			 * request was allocated but not sent
			 */
			spin_lock(&fc->bg_lock);
			if (!fc->blocked)
				wake_up(&fc->blocked_waitq);
			spin_unlock(&fc->bg_lock);
		}

		if (test_bit(FR_WAITING, &req->flags)) {
			__clear_bit(FR_WAITING, &req->flags);
			fuse_drop_waiting(fc);
		}

		fuse_request_free(req);
	}
}