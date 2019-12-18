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
struct hdac_bus {scalar_t__ codec_mask; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GCTL ; 
 int /*<<< orphan*/  STATESTS ; 
 int /*<<< orphan*/  STATESTS_INT_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snd_hdac_bus_enter_link_reset (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_bus_exit_link_reset (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_chip_readb (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdac_chip_readw (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writew (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int snd_hdac_bus_reset_link(struct hdac_bus *bus, bool full_reset)
{
	if (!full_reset)
		goto skip_reset;

	/* clear STATESTS */
	snd_hdac_chip_writew(bus, STATESTS, STATESTS_INT_MASK);

	/* reset controller */
	snd_hdac_bus_enter_link_reset(bus);

	/* delay for >= 100us for codec PLL to settle per spec
	 * Rev 0.9 section 5.5.1
	 */
	usleep_range(500, 1000);

	/* Bring controller out of reset */
	snd_hdac_bus_exit_link_reset(bus);

	/* Brent Chartrand said to wait >= 540us for codecs to initialize */
	usleep_range(1000, 1200);

 skip_reset:
	/* check to see if controller is ready */
	if (!snd_hdac_chip_readb(bus, GCTL)) {
		dev_dbg(bus->dev, "controller not ready!\n");
		return -EBUSY;
	}

	/* detect codecs */
	if (!bus->codec_mask) {
		bus->codec_mask = snd_hdac_chip_readw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%lx\n", bus->codec_mask);
	}

	return 0;
}