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
 int ENODEV ; 
 scalar_t__ is_bypassed_id (struct pci_dev*) ; 
 int usb_hcd_pci_probe (struct pci_dev*,struct pci_device_id const*) ; 

__attribute__((used)) static int ehci_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	if (is_bypassed_id(pdev))
		return -ENODEV;
	return usb_hcd_pci_probe(pdev, id);
}