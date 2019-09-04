#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssb_mipscore {TYPE_2__* dev; } ;
struct TYPE_3__ {int coreid; } ;
struct ssb_device {int irq; TYPE_1__ id; } ;
struct ssb_bus {unsigned int nr_devices; int chip_id; struct ssb_device* devices; int /*<<< orphan*/  chipco; int /*<<< orphan*/  extif; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; struct ssb_bus* bus; } ;

/* Variables and functions */
#define  SSB_DEV_80211 134 
#define  SSB_DEV_ETHERNET 133 
#define  SSB_DEV_ETHERNET_GBIT 132 
#define  SSB_DEV_EXTIF 131 
#define  SSB_DEV_PCI 130 
#define  SSB_DEV_USB11_HOST 129 
#define  SSB_DEV_USB20_HOST 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_irq (struct ssb_bus*) ; 
 int /*<<< orphan*/  set_irq (struct ssb_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ssb_chipco_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_chipco_timing_init (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long ssb_clockspeed (struct ssb_bus*) ; 
 scalar_t__ ssb_extif_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_extif_timing_init (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ssb_mips_flash_detect (struct ssb_mipscore*) ; 
 int ssb_mips_irq (struct ssb_device*) ; 
 int /*<<< orphan*/  ssb_mips_serial_init (struct ssb_mipscore*) ; 

void ssb_mipscore_init(struct ssb_mipscore *mcore)
{
	struct ssb_bus *bus;
	struct ssb_device *dev;
	unsigned long hz, ns;
	unsigned int irq, i;

	if (!mcore->dev)
		return; /* We don't have a MIPS core */

	dev_dbg(mcore->dev->dev, "Initializing MIPS core...\n");

	bus = mcore->dev->bus;
	hz = ssb_clockspeed(bus);
	if (!hz)
		hz = 100000000;
	ns = 1000000000 / hz;

	if (ssb_extif_available(&bus->extif))
		ssb_extif_timing_init(&bus->extif, ns);
	else if (ssb_chipco_available(&bus->chipco))
		ssb_chipco_timing_init(&bus->chipco, ns);

	/* Assign IRQs to all cores on the bus, start with irq line 2, because serial usually takes 1 */
	for (irq = 2, i = 0; i < bus->nr_devices; i++) {
		int mips_irq;
		dev = &(bus->devices[i]);
		mips_irq = ssb_mips_irq(dev);
		if (mips_irq > 4)
			dev->irq = 0;
		else
			dev->irq = mips_irq + 2;
		if (dev->irq > 5)
			continue;
		switch (dev->id.coreid) {
		case SSB_DEV_USB11_HOST:
			/* shouldn't need a separate irq line for non-4710, most of them have a proper
			 * external usb controller on the pci */
			if ((bus->chip_id == 0x4710) && (irq <= 4)) {
				set_irq(dev, irq++);
			}
			break;
		case SSB_DEV_PCI:
		case SSB_DEV_ETHERNET:
		case SSB_DEV_ETHERNET_GBIT:
		case SSB_DEV_80211:
		case SSB_DEV_USB20_HOST:
			/* These devices get their own IRQ line if available, the rest goes on IRQ0 */
			if (irq <= 4) {
				set_irq(dev, irq++);
				break;
			}
			/* fallthrough */
		case SSB_DEV_EXTIF:
			set_irq(dev, 0);
			break;
		}
	}
	dev_dbg(mcore->dev->dev, "after irq reconfiguration\n");
	dump_irq(bus);

	ssb_mips_serial_init(mcore);
	ssb_mips_flash_detect(mcore);
}