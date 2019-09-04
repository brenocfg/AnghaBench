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
struct dwc3_haps {int /*<<< orphan*/  dwc3; } ;

/* Variables and functions */
 struct dwc3_haps* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_haps_remove(struct pci_dev *pci)
{
	struct dwc3_haps *dwc = pci_get_drvdata(pci);

	platform_device_unregister(dwc->dwc3);
}