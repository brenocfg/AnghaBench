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
struct pci_dev {int dummy; } ;
struct dwc2_pci_glue {int /*<<< orphan*/  phy; int /*<<< orphan*/  dwc2; } ;

/* Variables and functions */
 struct dwc2_pci_glue* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_pci_remove(struct pci_dev *pci)
{
	struct dwc2_pci_glue *glue = pci_get_drvdata(pci);

	platform_device_unregister(glue->dwc2);
	usb_phy_generic_unregister(glue->phy);
	pci_set_drvdata(pci, NULL);
}