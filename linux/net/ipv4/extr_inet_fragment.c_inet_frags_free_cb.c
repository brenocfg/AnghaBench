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
struct inet_frag_queue {int flags; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int INET_FRAG_HASH_DEAD ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_frag_destroy (struct inet_frag_queue*) ; 
 scalar_t__ refcount_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inet_frags_free_cb(void *ptr, void *arg)
{
	struct inet_frag_queue *fq = ptr;
	int count;

	count = del_timer_sync(&fq->timer) ? 1 : 0;

	spin_lock_bh(&fq->lock);
	if (!(fq->flags & INET_FRAG_COMPLETE)) {
		fq->flags |= INET_FRAG_COMPLETE;
		count++;
	} else if (fq->flags & INET_FRAG_HASH_DEAD) {
		count++;
	}
	spin_unlock_bh(&fq->lock);

	if (refcount_sub_and_test(count, &fq->refcnt))
		inet_frag_destroy(fq);
}