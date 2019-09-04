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
struct intelfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 int /*<<< orphan*/  cleanup (struct intelfb_info*) ; 
 struct intelfb_info* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void intelfb_pci_unregister(struct pci_dev *pdev)
{
	struct intelfb_info *dinfo = pci_get_drvdata(pdev);

	DBG_MSG("intelfb_pci_unregister\n");

	if (!dinfo)
		return;

	cleanup(dinfo);
}