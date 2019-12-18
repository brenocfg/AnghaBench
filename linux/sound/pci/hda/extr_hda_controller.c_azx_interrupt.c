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
typedef  int u32 ;
struct hdac_bus {int /*<<< orphan*/  reg_lock; } ;
struct azx {int driver_caps; scalar_t__ disabled; TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_DCAPS_CTX_WORKAROUND ; 
 int /*<<< orphan*/  INTSTS ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  RIRBSTS ; 
 int RIRB_INT_MASK ; 
 int RIRB_INT_RESPONSE ; 
 struct hdac_bus* azx_bus (struct azx*) ; 
 scalar_t__ azx_has_pm_runtime (struct azx*) ; 
 int azx_readb (struct azx*,int /*<<< orphan*/ ) ; 
 int azx_readl (struct azx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_writeb (struct azx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_active (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdac_bus_handle_stream_irq (struct hdac_bus*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_bus_update_rirb (struct hdac_bus*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_update ; 
 int /*<<< orphan*/  udelay (int) ; 

irqreturn_t azx_interrupt(int irq, void *dev_id)
{
	struct azx *chip = dev_id;
	struct hdac_bus *bus = azx_bus(chip);
	u32 status;
	bool active, handled = false;
	int repeat = 0; /* count for avoiding endless loop */

#ifdef CONFIG_PM
	if (azx_has_pm_runtime(chip))
		if (!pm_runtime_active(chip->card->dev))
			return IRQ_NONE;
#endif

	spin_lock(&bus->reg_lock);

	if (chip->disabled)
		goto unlock;

	do {
		status = azx_readl(chip, INTSTS);
		if (status == 0 || status == 0xffffffff)
			break;

		handled = true;
		active = false;
		if (snd_hdac_bus_handle_stream_irq(bus, status, stream_update))
			active = true;

		/* clear rirb int */
		status = azx_readb(chip, RIRBSTS);
		if (status & RIRB_INT_MASK) {
			active = true;
			if (status & RIRB_INT_RESPONSE) {
				if (chip->driver_caps & AZX_DCAPS_CTX_WORKAROUND)
					udelay(80);
				snd_hdac_bus_update_rirb(bus);
			}
			azx_writeb(chip, RIRBSTS, RIRB_INT_MASK);
		}
	} while (active && ++repeat < 10);

 unlock:
	spin_unlock(&bus->reg_lock);

	return IRQ_RETVAL(handled);
}