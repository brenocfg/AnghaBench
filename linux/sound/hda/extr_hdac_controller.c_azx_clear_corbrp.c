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
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_CORBRP_RST ; 
 int /*<<< orphan*/  CORBRP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_hdac_chip_readw (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writew (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void azx_clear_corbrp(struct hdac_bus *bus)
{
	int timeout;

	for (timeout = 1000; timeout > 0; timeout--) {
		if (snd_hdac_chip_readw(bus, CORBRP) & AZX_CORBRP_RST)
			break;
		udelay(1);
	}
	if (timeout <= 0)
		dev_err(bus->dev, "CORB reset timeout#1, CORBRP = %d\n",
			snd_hdac_chip_readw(bus, CORBRP));

	snd_hdac_chip_writew(bus, CORBRP, 0);
	for (timeout = 1000; timeout > 0; timeout--) {
		if (snd_hdac_chip_readw(bus, CORBRP) == 0)
			break;
		udelay(1);
	}
	if (timeout <= 0)
		dev_err(bus->dev, "CORB reset timeout#2, CORBRP = %d\n",
			snd_hdac_chip_readw(bus, CORBRP));
}