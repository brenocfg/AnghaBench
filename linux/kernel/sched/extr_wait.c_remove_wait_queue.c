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
struct wait_queue_head {int /*<<< orphan*/  lock; } ;
struct wait_queue_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __remove_wait_queue (struct wait_queue_head*,struct wait_queue_entry*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void remove_wait_queue(struct wait_queue_head *wq_head, struct wait_queue_entry *wq_entry)
{
	unsigned long flags;

	spin_lock_irqsave(&wq_head->lock, flags);
	__remove_wait_queue(wq_head, wq_entry);
	spin_unlock_irqrestore(&wq_head->lock, flags);
}