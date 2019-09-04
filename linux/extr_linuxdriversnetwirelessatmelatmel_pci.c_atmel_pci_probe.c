#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* resource; int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_FW_TYPE_506 ; 
 int ENODEV ; 
 struct net_device* init_atmel_card (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int atmel_pci_probe(struct pci_dev *pdev,
				     const struct pci_device_id *pent)
{
	struct net_device *dev;

	if (pci_enable_device(pdev))
		return -ENODEV;

	pci_set_master(pdev);

	dev = init_atmel_card(pdev->irq, pdev->resource[1].start,
			      ATMEL_FW_TYPE_506,
			      &pdev->dev, NULL, NULL);
	if (!dev) {
		pci_disable_device(pdev);
		return -ENODEV;
	}

	pci_set_drvdata(pdev, dev);
	return 0;
}