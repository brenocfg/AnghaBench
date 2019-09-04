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
struct xen_pcibk_dev_data {int /*<<< orphan*/  config_fields; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct xen_pcibk_dev_data* pci_get_drvdata (struct pci_dev*) ; 
 int xen_pcibk_config_capability_add_fields (struct pci_dev*) ; 
 int xen_pcibk_config_header_add_fields (struct pci_dev*) ; 
 int xen_pcibk_config_quirks_init (struct pci_dev*) ; 

int xen_pcibk_config_init_dev(struct pci_dev *dev)
{
	int err = 0;
	struct xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);

	dev_dbg(&dev->dev, "initializing virtual configuration space\n");

	INIT_LIST_HEAD(&dev_data->config_fields);

	err = xen_pcibk_config_header_add_fields(dev);
	if (err)
		goto out;

	err = xen_pcibk_config_capability_add_fields(dev);
	if (err)
		goto out;

	err = xen_pcibk_config_quirks_init(dev);

out:
	return err;
}