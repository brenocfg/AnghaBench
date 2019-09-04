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
struct xen_9pfs_dataring {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; TYPE_1__* priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t xen_9pfs_front_event_handler(int irq, void *r)
{
	struct xen_9pfs_dataring *ring = r;

	if (!ring || !ring->priv->client) {
		/* ignore spurious interrupt */
		return IRQ_HANDLED;
	}

	wake_up_interruptible(&ring->wq);
	schedule_work(&ring->work);

	return IRQ_HANDLED;
}