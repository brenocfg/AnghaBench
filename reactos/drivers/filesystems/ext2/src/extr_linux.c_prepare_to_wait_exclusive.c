#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  struct __wait_queue* wait_queue_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ wait_queue_head_t ;
struct __wait_queue {int /*<<< orphan*/  task_list; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WQ_FLAG_EXCLUSIVE ; 
 int /*<<< orphan*/  __add_wait_queue_tail (TYPE_1__*,struct __wait_queue*) ; 
 scalar_t__ is_sync_wait (struct __wait_queue*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
prepare_to_wait_exclusive(wait_queue_head_t *q, wait_queue_t *waiti, int state)
{
    unsigned long flags;
    struct __wait_queue *wait = *waiti;

    wait->flags |= WQ_FLAG_EXCLUSIVE;
    spin_lock_irqsave(&q->lock, flags);
    if (list_empty(&wait->task_list))
        __add_wait_queue_tail(q, wait);
    /*
     * don't alter the task state if this is just going to
      * queue an async wait queue callback
     */
    if (is_sync_wait(wait))
        set_current_state(state);
    spin_unlock_irqrestore(&q->lock, flags);
}