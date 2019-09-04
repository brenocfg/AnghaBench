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
struct spi_controller {int running; int /*<<< orphan*/  dev; int /*<<< orphan*/  queue_lock; scalar_t__ busy; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int spi_stop_queue(struct spi_controller *ctlr)
{
	unsigned long flags;
	unsigned limit = 500;
	int ret = 0;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	/*
	 * This is a bit lame, but is optimized for the common execution path.
	 * A wait_queue on the ctlr->busy could be used, but then the common
	 * execution path (pump_messages) would be required to call wake_up or
	 * friends on every SPI message. Do this instead.
	 */
	while ((!list_empty(&ctlr->queue) || ctlr->busy) && limit--) {
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		usleep_range(10000, 11000);
		spin_lock_irqsave(&ctlr->queue_lock, flags);
	}

	if (!list_empty(&ctlr->queue) || ctlr->busy)
		ret = -EBUSY;
	else
		ctlr->running = false;

	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	if (ret) {
		dev_warn(&ctlr->dev, "could not stop message queue\n");
		return ret;
	}
	return ret;
}