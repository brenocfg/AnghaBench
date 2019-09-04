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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  probe_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xb_waitq ; 
 int xenstored_ready ; 

__attribute__((used)) static irqreturn_t wake_waiting(int irq, void *unused)
{
	if (unlikely(xenstored_ready == 0)) {
		xenstored_ready = 1;
		schedule_work(&probe_work);
	}

	wake_up(&xb_waitq);
	return IRQ_HANDLED;
}