#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct esb_dev {TYPE_1__* pdev; int /*<<< orphan*/ * base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESB_MODULE_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct esb_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 scalar_t__ pci_enable_device (TYPE_1__*) ; 
 int /*<<< orphan*/ * pci_ioremap_bar (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_request_region (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char esb_getdevice(struct esb_dev *edev)
{
	if (pci_enable_device(edev->pdev)) {
		dev_err(&edev->pdev->dev, "failed to enable device\n");
		goto err_devput;
	}

	if (pci_request_region(edev->pdev, 0, ESB_MODULE_NAME)) {
		dev_err(&edev->pdev->dev, "failed to request region\n");
		goto err_disable;
	}

	edev->base = pci_ioremap_bar(edev->pdev, 0);
	if (edev->base == NULL) {
		/* Something's wrong here, BASEADDR has to be set */
		dev_err(&edev->pdev->dev, "failed to get BASEADDR\n");
		goto err_release;
	}

	/* Done */
	dev_set_drvdata(&edev->pdev->dev, edev);
	return 1;

err_release:
	pci_release_region(edev->pdev, 0);
err_disable:
	pci_disable_device(edev->pdev);
err_devput:
	return 0;
}