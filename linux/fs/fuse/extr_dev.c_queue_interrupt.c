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
struct fuse_iqueue {int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  interrupts; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wake_interrupt_and_unlock ) (struct fuse_iqueue*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FR_FINISHED ; 
 int /*<<< orphan*/  FR_INTERRUPTED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fuse_iqueue*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int queue_interrupt(struct fuse_iqueue *fiq, struct fuse_req *req)
{
	spin_lock(&fiq->lock);
	/* Check for we've sent request to interrupt this req */
	if (unlikely(!test_bit(FR_INTERRUPTED, &req->flags))) {
		spin_unlock(&fiq->lock);
		return -EINVAL;
	}

	if (list_empty(&req->intr_entry)) {
		list_add_tail(&req->intr_entry, &fiq->interrupts);
		/*
		 * Pairs with smp_mb() implied by test_and_set_bit()
		 * from request_end().
		 */
		smp_mb();
		if (test_bit(FR_FINISHED, &req->flags)) {
			list_del_init(&req->intr_entry);
			spin_unlock(&fiq->lock);
			return 0;
		}
		fiq->ops->wake_interrupt_and_unlock(fiq);
	} else {
		spin_unlock(&fiq->lock);
	}
	return 0;
}