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
struct TYPE_2__ {int coreid; } ;
struct ssb_device {struct device* dev; struct device* dma_dev; TYPE_1__ id; } ;
struct ssb_bus {int nr_devices; int bustype; int /*<<< orphan*/  busnumber; struct ssb_device* devices; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; } ;
struct __ssb_dev_wrapper {struct ssb_device* sdev; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  SSB_BUSTYPE_PCI 138 
#define  SSB_BUSTYPE_PCMCIA 137 
#define  SSB_BUSTYPE_SDIO 136 
#define  SSB_BUSTYPE_SSB 135 
#define  SSB_DEV_CHIPCOMMON 134 
#define  SSB_DEV_EXTIF 133 
#define  SSB_DEV_MIPS 132 
#define  SSB_DEV_MIPS_3302 131 
#define  SSB_DEV_PCI 130 
#define  SSB_DEV_PCIE 129 
#define  SSB_DEV_PCMCIA 128 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int device_register (struct device*) ; 
 struct __ssb_dev_wrapper* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  ssb_bustype ; 
 int /*<<< orphan*/  ssb_devices_unregister (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_release_dev ; 

__attribute__((used)) static int ssb_devices_register(struct ssb_bus *bus)
{
	struct ssb_device *sdev;
	struct device *dev;
	struct __ssb_dev_wrapper *devwrap;
	int i, err = 0;
	int dev_idx = 0;

	for (i = 0; i < bus->nr_devices; i++) {
		sdev = &(bus->devices[i]);

		/* We don't register SSB-system devices to the kernel,
		 * as the drivers for them are built into SSB. */
		switch (sdev->id.coreid) {
		case SSB_DEV_CHIPCOMMON:
		case SSB_DEV_PCI:
		case SSB_DEV_PCIE:
		case SSB_DEV_PCMCIA:
		case SSB_DEV_MIPS:
		case SSB_DEV_MIPS_3302:
		case SSB_DEV_EXTIF:
			continue;
		}

		devwrap = kzalloc(sizeof(*devwrap), GFP_KERNEL);
		if (!devwrap) {
			err = -ENOMEM;
			goto error;
		}
		dev = &devwrap->dev;
		devwrap->sdev = sdev;

		dev->release = ssb_release_dev;
		dev->bus = &ssb_bustype;
		dev_set_name(dev, "ssb%u:%d", bus->busnumber, dev_idx);

		switch (bus->bustype) {
		case SSB_BUSTYPE_PCI:
#ifdef CONFIG_SSB_PCIHOST
			sdev->irq = bus->host_pci->irq;
			dev->parent = &bus->host_pci->dev;
			sdev->dma_dev = dev->parent;
#endif
			break;
		case SSB_BUSTYPE_PCMCIA:
#ifdef CONFIG_SSB_PCMCIAHOST
			sdev->irq = bus->host_pcmcia->irq;
			dev->parent = &bus->host_pcmcia->dev;
#endif
			break;
		case SSB_BUSTYPE_SDIO:
#ifdef CONFIG_SSB_SDIOHOST
			dev->parent = &bus->host_sdio->dev;
#endif
			break;
		case SSB_BUSTYPE_SSB:
			dev->dma_mask = &dev->coherent_dma_mask;
			sdev->dma_dev = dev;
			break;
		}

		sdev->dev = dev;
		err = device_register(dev);
		if (err) {
			pr_err("Could not register %s\n", dev_name(dev));
			/* Set dev to NULL to not unregister
			 * dev on error unwinding. */
			sdev->dev = NULL;
			put_device(dev);
			goto error;
		}
		dev_idx++;
	}

#ifdef CONFIG_SSB_DRIVER_MIPS
	if (bus->mipscore.pflash.present) {
		err = platform_device_register(&ssb_pflash_dev);
		if (err)
			pr_err("Error registering parallel flash\n");
	}
#endif

#ifdef CONFIG_SSB_SFLASH
	if (bus->mipscore.sflash.present) {
		err = platform_device_register(&ssb_sflash_dev);
		if (err)
			pr_err("Error registering serial flash\n");
	}
#endif

	return 0;
error:
	/* Unwind the already registered devices. */
	ssb_devices_unregister(bus);
	return err;
}