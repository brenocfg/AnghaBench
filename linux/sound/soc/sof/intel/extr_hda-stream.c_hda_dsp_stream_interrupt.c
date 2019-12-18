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
typedef  int u32 ;
struct hdac_bus {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  dev; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTSTS ; 
 int IRQ_NONE ; 
 int IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int snd_hdac_chip_readl (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

irqreturn_t hda_dsp_stream_interrupt(int irq, void *context)
{
	struct hdac_bus *bus = context;
	int ret = IRQ_WAKE_THREAD;
	u32 status;

	spin_lock(&bus->reg_lock);

	status = snd_hdac_chip_readl(bus, INTSTS);
	dev_vdbg(bus->dev, "stream irq, INTSTS status: 0x%x\n", status);

	/* Register inaccessible, ignore it.*/
	if (status == 0xffffffff)
		ret = IRQ_NONE;

	spin_unlock(&bus->reg_lock);

	return ret;
}