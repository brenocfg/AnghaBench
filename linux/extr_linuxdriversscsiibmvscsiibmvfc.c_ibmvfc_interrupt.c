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
struct ibmvfc_host {TYPE_1__* host; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_disable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ibmvfc_interrupt(int irq, void *dev_instance)
{
	struct ibmvfc_host *vhost = (struct ibmvfc_host *)dev_instance;
	unsigned long flags;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	vio_disable_interrupts(to_vio_dev(vhost->dev));
	tasklet_schedule(&vhost->tasklet);
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
	return IRQ_HANDLED;
}