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
struct ssb_bus {int dummy; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ssb_bus*) ; 
 struct ssb_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char const*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ssb_bus*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 int ssb_bus_pcibus_register (struct ssb_bus*,struct pci_dev*) ; 

__attribute__((used)) static int ssb_pcihost_probe(struct pci_dev *dev,
			     const struct pci_device_id *id)
{
	struct ssb_bus *ssb;
	int err = -ENOMEM;
	const char *name;
	u32 val;

	ssb = kzalloc(sizeof(*ssb), GFP_KERNEL);
	if (!ssb)
		goto out;
	err = pci_enable_device(dev);
	if (err)
		goto err_kfree_ssb;
	name = dev_name(&dev->dev);
	if (dev->driver && dev->driver->name)
		name = dev->driver->name;
	err = pci_request_regions(dev, name);
	if (err)
		goto err_pci_disable;
	pci_set_master(dev);

	/* Disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state */
	pci_read_config_dword(dev, 0x40, &val);
	if ((val & 0x0000ff00) != 0)
		pci_write_config_dword(dev, 0x40, val & 0xffff00ff);

	err = ssb_bus_pcibus_register(ssb, dev);
	if (err)
		goto err_pci_release_regions;

	pci_set_drvdata(dev, ssb);

out:
	return err;

err_pci_release_regions:
	pci_release_regions(dev);
err_pci_disable:
	pci_disable_device(dev);
err_kfree_ssb:
	kfree(ssb);
	return err;
}