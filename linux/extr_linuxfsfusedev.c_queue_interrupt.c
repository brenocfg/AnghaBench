#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fuse_req {int /*<<< orphan*/  intr_entry; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fuse_iqueue {int /*<<< orphan*/  fasync; TYPE_1__ waitq; int /*<<< orphan*/  interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_FINISHED ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_locked (TYPE_1__*) ; 

__attribute__((used)) static void queue_interrupt(struct fuse_iqueue *fiq, struct fuse_req *req)
{
	spin_lock(&fiq->waitq.lock);
	if (test_bit(FR_FINISHED, &req->flags)) {
		spin_unlock(&fiq->waitq.lock);
		return;
	}
	if (list_empty(&req->intr_entry)) {
		list_add_tail(&req->intr_entry, &fiq->interrupts);
		wake_up_locked(&fiq->waitq);
	}
	spin_unlock(&fiq->waitq.lock);
	kill_fasync(&fiq->fasync, SIGIO, POLL_IN);
}