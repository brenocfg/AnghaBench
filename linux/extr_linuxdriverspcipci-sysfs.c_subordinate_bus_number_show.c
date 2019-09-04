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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PCI_SUBORDINATE_BUS ; 
 int pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t subordinate_bus_number_show(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct pci_dev *pci_dev = to_pci_dev(dev);
	u8 sub_bus;
	int err;

	err = pci_read_config_byte(pci_dev, PCI_SUBORDINATE_BUS, &sub_bus);
	if (err)
		return -EINVAL;

	return sprintf(buf, "%u\n", sub_bus);
}