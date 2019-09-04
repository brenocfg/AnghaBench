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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTSTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  RIRBSTS ; 
 int RIRB_INT_MASK ; 
 int RIRB_INT_RESPONSE ; 
 int /*<<< orphan*/  pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_bus_update_rirb (struct hdac_bus*) ; 
 int snd_hdac_chip_readb (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int snd_hdac_chip_readl (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writeb (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t skl_interrupt(int irq, void *dev_id)
{
	struct hdac_bus *bus = dev_id;
	u32 status;

	if (!pm_runtime_active(bus->dev))
		return IRQ_NONE;

	spin_lock(&bus->reg_lock);

	status = snd_hdac_chip_readl(bus, INTSTS);
	if (status == 0 || status == 0xffffffff) {
		spin_unlock(&bus->reg_lock);
		return IRQ_NONE;
	}

	/* clear rirb int */
	status = snd_hdac_chip_readb(bus, RIRBSTS);
	if (status & RIRB_INT_MASK) {
		if (status & RIRB_INT_RESPONSE)
			snd_hdac_bus_update_rirb(bus);
		snd_hdac_chip_writeb(bus, RIRBSTS, RIRB_INT_MASK);
	}

	spin_unlock(&bus->reg_lock);

	return snd_hdac_chip_readl(bus, INTSTS) ? IRQ_WAKE_THREAD : IRQ_HANDLED;
}