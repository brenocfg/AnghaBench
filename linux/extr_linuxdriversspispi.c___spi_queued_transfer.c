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
struct spi_message {int /*<<< orphan*/  queue; int /*<<< orphan*/  status; scalar_t__ actual_length; } ;
struct spi_device {struct spi_controller* controller; } ;
struct spi_controller {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  pump_messages; int /*<<< orphan*/  kworker; int /*<<< orphan*/  busy; int /*<<< orphan*/  queue; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __spi_queued_transfer(struct spi_device *spi,
				 struct spi_message *msg,
				 bool need_pump)
{
	struct spi_controller *ctlr = spi->controller;
	unsigned long flags;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	if (!ctlr->running) {
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		return -ESHUTDOWN;
	}
	msg->actual_length = 0;
	msg->status = -EINPROGRESS;

	list_add_tail(&msg->queue, &ctlr->queue);
	if (!ctlr->busy && need_pump)
		kthread_queue_work(&ctlr->kworker, &ctlr->pump_messages);

	spin_unlock_irqrestore(&ctlr->queue_lock, flags);
	return 0;
}