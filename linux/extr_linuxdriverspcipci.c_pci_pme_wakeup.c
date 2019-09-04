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
struct pci_dev {int pme_poll; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ pci_check_pme_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_wakeup_event (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_request_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci_pme_wakeup(struct pci_dev *dev, void *pme_poll_reset)
{
	if (pme_poll_reset && dev->pme_poll)
		dev->pme_poll = false;

	if (pci_check_pme_status(dev)) {
		pci_wakeup_event(dev);
		pm_request_resume(&dev->dev);
	}
	return 0;
}