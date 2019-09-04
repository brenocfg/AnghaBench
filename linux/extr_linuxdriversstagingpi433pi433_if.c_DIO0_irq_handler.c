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
struct pi433_device {scalar_t__* irq_state; int /*<<< orphan*/  fifo_wait_queue; scalar_t__ free_in_fifo; int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_wait_queue; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t DIO0 ; 
 scalar_t__ DIO_PACKET_SENT ; 
 scalar_t__ DIO_PAYLOAD_READY ; 
 scalar_t__ DIO_RSSI_DIO0 ; 
 scalar_t__ FIFO_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t DIO0_irq_handler(int irq, void *dev_id)
{
	struct pi433_device *device = dev_id;

	if (device->irq_state[DIO0] == DIO_PACKET_SENT) {
		device->free_in_fifo = FIFO_SIZE;
		dev_dbg(device->dev, "DIO0 irq: Packet sent\n");
		wake_up_interruptible(&device->fifo_wait_queue);
	} else if (device->irq_state[DIO0] == DIO_RSSI_DIO0) {
		dev_dbg(device->dev, "DIO0 irq: RSSI level over threshold\n");
		wake_up_interruptible(&device->rx_wait_queue);
	} else if (device->irq_state[DIO0] == DIO_PAYLOAD_READY) {
		dev_dbg(device->dev, "DIO0 irq: Payload ready\n");
		device->free_in_fifo = 0;
		wake_up_interruptible(&device->fifo_wait_queue);
	}

	return IRQ_HANDLED;
}