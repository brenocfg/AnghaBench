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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ wait_queue_head_t ;
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageWaiters (struct page*) ; 
 int /*<<< orphan*/  __add_wait_queue_entry_tail (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* page_waitqueue (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void add_page_wait_queue(struct page *page, wait_queue_entry_t *waiter)
{
	wait_queue_head_t *q = page_waitqueue(page);
	unsigned long flags;

	spin_lock_irqsave(&q->lock, flags);
	__add_wait_queue_entry_tail(q, waiter);
	SetPageWaiters(page);
	spin_unlock_irqrestore(&q->lock, flags);
}