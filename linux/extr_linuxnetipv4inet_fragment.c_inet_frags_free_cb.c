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
struct inet_frag_queue {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_frag_put (struct inet_frag_queue*) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inet_frags_free_cb(void *ptr, void *arg)
{
	struct inet_frag_queue *fq = ptr;

	/* If we can not cancel the timer, it means this frag_queue
	 * is already disappearing, we have nothing to do.
	 * Otherwise, we own a refcount until the end of this function.
	 */
	if (!del_timer(&fq->timer))
		return;

	spin_lock_bh(&fq->lock);
	if (!(fq->flags & INET_FRAG_COMPLETE)) {
		fq->flags |= INET_FRAG_COMPLETE;
		refcount_dec(&fq->refcnt);
	}
	spin_unlock_bh(&fq->lock);

	inet_frag_put(fq);
}