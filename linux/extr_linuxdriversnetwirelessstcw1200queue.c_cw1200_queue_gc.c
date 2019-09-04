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
struct timer_list {int dummy; } ;
struct cw1200_queue {int /*<<< orphan*/  stats; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cw1200_queue_gc (struct cw1200_queue*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cw1200_queue_post_gc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cw1200_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc ; 
 int /*<<< orphan*/  list ; 
 struct cw1200_queue* queue ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cw1200_queue_gc(struct timer_list *t)
{
	LIST_HEAD(list);
	struct cw1200_queue *queue =
		from_timer(queue, t, gc);

	spin_lock_bh(&queue->lock);
	__cw1200_queue_gc(queue, &list, true);
	spin_unlock_bh(&queue->lock);
	cw1200_queue_post_gc(queue->stats, &list);
}