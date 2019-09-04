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
struct velocity_info_tbl {int dummy; } ;
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_PCI ; 
 int /*<<< orphan*/  VELOCITY_NAME ; 
 struct velocity_info_tbl* chip_info_table ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int velocity_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct velocity_info_tbl const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int velocity_pci_probe(struct pci_dev *pdev,
			       const struct pci_device_id *ent)
{
	const struct velocity_info_tbl *info =
					&chip_info_table[ent->driver_data];
	int ret;

	ret = pci_enable_device(pdev);
	if (ret < 0)
		return ret;

	ret = pci_request_regions(pdev, VELOCITY_NAME);
	if (ret < 0) {
		dev_err(&pdev->dev, "No PCI resources.\n");
		goto fail1;
	}

	ret = velocity_probe(&pdev->dev, pdev->irq, info, BUS_PCI);
	if (ret == 0)
		return 0;

	pci_release_regions(pdev);
fail1:
	pci_disable_device(pdev);
	return ret;
}