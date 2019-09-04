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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  device_init (int /*<<< orphan*/ ,struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  printk (char*,struct pci_dev*) ; 
 int /*<<< orphan*/  slgt_device_count ; 

__attribute__((used)) static int init_one(struct pci_dev *dev,
			      const struct pci_device_id *ent)
{
	if (pci_enable_device(dev)) {
		printk("error enabling pci device %p\n", dev);
		return -EIO;
	}
	pci_set_master(dev);
	device_init(slgt_device_count, dev);
	return 0;
}