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
struct pcie_pme_service_data {int dummy; } ;
struct pcie_device {int /*<<< orphan*/  irq; struct pci_dev* port; } ;
struct pci_dev {int /*<<< orphan*/  subordinate; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 struct pcie_pme_service_data* get_service_data (struct pcie_device*) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int pcie_pme_check_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_pme_disable_interrupt (struct pci_dev*,struct pcie_pme_service_data*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcie_pme_suspend(struct pcie_device *srv)
{
	struct pcie_pme_service_data *data = get_service_data(srv);
	struct pci_dev *port = srv->port;
	bool wakeup;
	int ret;

	if (device_may_wakeup(&port->dev)) {
		wakeup = true;
	} else {
		down_read(&pci_bus_sem);
		wakeup = pcie_pme_check_wakeup(port->subordinate);
		up_read(&pci_bus_sem);
	}
	if (wakeup) {
		ret = enable_irq_wake(srv->irq);
		if (!ret)
			return 0;
	}

	pcie_pme_disable_interrupt(port, data);

	synchronize_irq(srv->irq);

	return 0;
}