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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_wakeup_event (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_request_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci_wakeup(struct pci_dev *pci_dev, void *ign)
{
	pci_wakeup_event(pci_dev);
	pm_request_resume(&pci_dev->dev);
	return 0;
}