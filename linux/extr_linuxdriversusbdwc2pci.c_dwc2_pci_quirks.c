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
struct property_entry {int dummy; } ;
struct platform_device {int dummy; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_PRODUCT_ID_HAPS_HSOTG ; 
 scalar_t__ PCI_VENDOR_ID_SYNOPSYS ; 
 int platform_device_add_properties (struct platform_device*,struct property_entry*) ; 

__attribute__((used)) static int dwc2_pci_quirks(struct pci_dev *pdev, struct platform_device *dwc2)
{
	if (pdev->vendor == PCI_VENDOR_ID_SYNOPSYS &&
	    pdev->device == PCI_PRODUCT_ID_HAPS_HSOTG) {
		struct property_entry properties[] = {
			{ },
		};

		return platform_device_add_properties(dwc2, properties);
	}

	return 0;
}