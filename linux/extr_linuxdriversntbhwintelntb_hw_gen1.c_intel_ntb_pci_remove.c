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
struct intel_ntb_dev {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_ntb_deinit_pci (struct intel_ntb_dev*) ; 
 int /*<<< orphan*/  kfree (struct intel_ntb_dev*) ; 
 int /*<<< orphan*/  ndev_deinit_debugfs (struct intel_ntb_dev*) ; 
 int /*<<< orphan*/  ntb_unregister_device (int /*<<< orphan*/ *) ; 
 struct intel_ntb_dev* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pdev_is_gen1 (struct pci_dev*) ; 
 scalar_t__ pdev_is_gen3 (struct pci_dev*) ; 
 int /*<<< orphan*/  xeon_deinit_dev (struct intel_ntb_dev*) ; 

__attribute__((used)) static void intel_ntb_pci_remove(struct pci_dev *pdev)
{
	struct intel_ntb_dev *ndev = pci_get_drvdata(pdev);

	ntb_unregister_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	if (pdev_is_gen1(pdev) || pdev_is_gen3(pdev))
		xeon_deinit_dev(ndev);
	intel_ntb_deinit_pci(ndev);
	kfree(ndev);
}