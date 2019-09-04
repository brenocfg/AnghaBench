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
struct TYPE_2__ {scalar_t__ count; } ;
struct slgt_info {int irq_occurred; unsigned int port_count; int bh_requested; int /*<<< orphan*/  irq_level; int /*<<< orphan*/  lock; int /*<<< orphan*/  task; int /*<<< orphan*/  device_name; int /*<<< orphan*/  bh_running; scalar_t__ pending_bh; scalar_t__ netcount; TYPE_1__ port; struct slgt_info** port_array; scalar_t__ gpio_present; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int BIT16 ; 
 unsigned int BIT17 ; 
 unsigned int BIT8 ; 
 int /*<<< orphan*/  DBGISR (char*) ; 
 int /*<<< orphan*/  GSR ; 
 int /*<<< orphan*/  IOSR ; 
 int /*<<< orphan*/  IOVR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  isr_gpio (struct slgt_info*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  isr_rdma (struct slgt_info*) ; 
 int /*<<< orphan*/  isr_serial (struct slgt_info*) ; 
 int /*<<< orphan*/  isr_tdma (struct slgt_info*) ; 
 int rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_reg32 (struct slgt_info*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t slgt_interrupt(int dummy, void *dev_id)
{
	struct slgt_info *info = dev_id;
	unsigned int gsr;
	unsigned int i;

	DBGISR(("slgt_interrupt irq=%d entry\n", info->irq_level));

	while((gsr = rd_reg32(info, GSR) & 0xffffff00)) {
		DBGISR(("%s gsr=%08x\n", info->device_name, gsr));
		info->irq_occurred = true;
		for(i=0; i < info->port_count ; i++) {
			if (info->port_array[i] == NULL)
				continue;
			spin_lock(&info->port_array[i]->lock);
			if (gsr & (BIT8 << i))
				isr_serial(info->port_array[i]);
			if (gsr & (BIT16 << (i*2)))
				isr_rdma(info->port_array[i]);
			if (gsr & (BIT17 << (i*2)))
				isr_tdma(info->port_array[i]);
			spin_unlock(&info->port_array[i]->lock);
		}
	}

	if (info->gpio_present) {
		unsigned int state;
		unsigned int changed;
		spin_lock(&info->lock);
		while ((changed = rd_reg32(info, IOSR)) != 0) {
			DBGISR(("%s iosr=%08x\n", info->device_name, changed));
			/* read latched state of GPIO signals */
			state = rd_reg32(info, IOVR);
			/* clear pending GPIO interrupt bits */
			wr_reg32(info, IOSR, changed);
			for (i=0 ; i < info->port_count ; i++) {
				if (info->port_array[i] != NULL)
					isr_gpio(info->port_array[i], changed, state);
			}
		}
		spin_unlock(&info->lock);
	}

	for(i=0; i < info->port_count ; i++) {
		struct slgt_info *port = info->port_array[i];
		if (port == NULL)
			continue;
		spin_lock(&port->lock);
		if ((port->port.count || port->netcount) &&
		    port->pending_bh && !port->bh_running &&
		    !port->bh_requested) {
			DBGISR(("%s bh queued\n", port->device_name));
			schedule_work(&port->task);
			port->bh_requested = true;
		}
		spin_unlock(&port->lock);
	}

	DBGISR(("slgt_interrupt irq=%d exit\n", info->irq_level));
	return IRQ_HANDLED;
}