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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  io_offset ; 
 int pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  piix4_pm_io_region ; 
 int /*<<< orphan*/  piix4_poweroff ; 
 struct pci_dev* pm_dev ; 
 int /*<<< orphan*/  pm_power_off ; 

__attribute__((used)) static int piix4_poweroff_probe(struct pci_dev *dev,
				const struct pci_device_id *id)
{
	int res;

	if (pm_dev)
		return -EINVAL;

	/* Request access to the PIIX4 PM IO registers */
	res = pci_request_region(dev, piix4_pm_io_region,
				 "PIIX4 PM IO registers");
	if (res) {
		dev_err(&dev->dev, "failed to request PM IO registers: %d\n",
			res);
		return res;
	}

	pm_dev = dev;
	io_offset = pci_resource_start(dev, piix4_pm_io_region);
	pm_power_off = piix4_poweroff;

	return 0;
}