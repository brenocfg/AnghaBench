#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dim_channel {int dummy; } ;
struct dim2_hdm {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {unsigned long data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHANNELS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 TYPE_1__ dim2_tasklet ; 
 int /*<<< orphan*/  dim_lock ; 
 int /*<<< orphan*/  dim_service_ahb_int_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_active_channels (struct dim2_hdm*,struct dim_channel**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t dim2_ahb_isr(int irq, void *_dev)
{
	struct dim2_hdm *dev = _dev;
	struct dim_channel *buffer[DMA_CHANNELS + 1];
	unsigned long flags;

	spin_lock_irqsave(&dim_lock, flags);
	dim_service_ahb_int_irq(get_active_channels(dev, buffer));
	spin_unlock_irqrestore(&dim_lock, flags);

	dim2_tasklet.data = (unsigned long)dev;
	tasklet_schedule(&dim2_tasklet);
	return IRQ_HANDLED;
}