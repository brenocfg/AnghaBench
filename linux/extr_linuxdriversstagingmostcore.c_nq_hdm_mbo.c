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
struct most_channel {int /*<<< orphan*/  hdm_fifo_wq; int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  halt_fifo; } ;
struct mbo {int /*<<< orphan*/  list; struct most_channel* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nq_hdm_mbo(struct mbo *mbo)
{
	unsigned long flags;
	struct most_channel *c = mbo->context;

	spin_lock_irqsave(&c->fifo_lock, flags);
	list_add_tail(&mbo->list, &c->halt_fifo);
	spin_unlock_irqrestore(&c->fifo_lock, flags);
	wake_up_interruptible(&c->hdm_fifo_wq);
}