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
struct hdac_bus {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZX_GCTL_UNSOL ; 
 int /*<<< orphan*/  CORBCTL ; 
 int /*<<< orphan*/  GCTL ; 
 int /*<<< orphan*/  RIRBCTL ; 
 int /*<<< orphan*/  hdac_wait_for_cmd_dmas (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writeb (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void snd_hdac_bus_stop_cmd_io(struct hdac_bus *bus)
{
	spin_lock_irq(&bus->reg_lock);
	/* disable ringbuffer DMAs */
	snd_hdac_chip_writeb(bus, RIRBCTL, 0);
	snd_hdac_chip_writeb(bus, CORBCTL, 0);
	spin_unlock_irq(&bus->reg_lock);

	hdac_wait_for_cmd_dmas(bus);

	spin_lock_irq(&bus->reg_lock);
	/* disable unsolicited responses */
	snd_hdac_chip_updatel(bus, GCTL, AZX_GCTL_UNSOL, 0);
	spin_unlock_irq(&bus->reg_lock);
}