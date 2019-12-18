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
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int AZX_REG_VS_D0I3C_CIP ; 
 int AZX_REG_VS_D0I3C_I3 ; 
 int /*<<< orphan*/  VS_D0I3C ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hdac_bus* pci_get_drvdata (struct pci_dev*) ; 
 int snd_hdac_chip_readb (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writeb (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void skl_update_d0i3c(struct device *dev, bool enable)
{
	struct pci_dev *pci = to_pci_dev(dev);
	struct hdac_bus *bus = pci_get_drvdata(pci);
	u8 reg;
	int timeout = 50;

	reg = snd_hdac_chip_readb(bus, VS_D0I3C);
	/* Do not write to D0I3C until command in progress bit is cleared */
	while ((reg & AZX_REG_VS_D0I3C_CIP) && --timeout) {
		udelay(10);
		reg = snd_hdac_chip_readb(bus, VS_D0I3C);
	}

	/* Highly unlikely. But if it happens, flag error explicitly */
	if (!timeout) {
		dev_err(bus->dev, "Before D0I3C update: D0I3C CIP timeout\n");
		return;
	}

	if (enable)
		reg = reg | AZX_REG_VS_D0I3C_I3;
	else
		reg = reg & (~AZX_REG_VS_D0I3C_I3);

	snd_hdac_chip_writeb(bus, VS_D0I3C, reg);

	timeout = 50;
	/* Wait for cmd in progress to be cleared before exiting the function */
	reg = snd_hdac_chip_readb(bus, VS_D0I3C);
	while ((reg & AZX_REG_VS_D0I3C_CIP) && --timeout) {
		udelay(10);
		reg = snd_hdac_chip_readb(bus, VS_D0I3C);
	}

	/* Highly unlikely. But if it happens, flag error explicitly */
	if (!timeout) {
		dev_err(bus->dev, "After D0I3C update: D0I3C CIP timeout\n");
		return;
	}

	dev_dbg(bus->dev, "D0I3C register = 0x%x\n",
			snd_hdac_chip_readb(bus, VS_D0I3C));
}