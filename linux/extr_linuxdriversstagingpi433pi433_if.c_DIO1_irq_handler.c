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
struct pi433_device {scalar_t__* irq_state; int /*<<< orphan*/  fifo_wait_queue; void* free_in_fifo; int /*<<< orphan*/  dev; scalar_t__ rx_active; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t DIO1 ; 
 scalar_t__ DIO_FIFO_LEVEL ; 
 scalar_t__ DIO_FIFO_NOT_EMPTY_DIO1 ; 
 void* FIFO_SIZE ; 
 void* FIFO_THRESHOLD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t DIO1_irq_handler(int irq, void *dev_id)
{
	struct pi433_device *device = dev_id;

	if (device->irq_state[DIO1] == DIO_FIFO_NOT_EMPTY_DIO1) {
		device->free_in_fifo = FIFO_SIZE;
	} else if (device->irq_state[DIO1] == DIO_FIFO_LEVEL) {
		if (device->rx_active)
			device->free_in_fifo = FIFO_THRESHOLD - 1;
		else
			device->free_in_fifo = FIFO_SIZE - FIFO_THRESHOLD - 1;
	}
	dev_dbg(device->dev,
		"DIO1 irq: %d bytes free in fifo\n", device->free_in_fifo);
	wake_up_interruptible(&device->fifo_wait_queue);

	return IRQ_HANDLED;
}