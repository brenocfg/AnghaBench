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
struct xgene_msi {int /*<<< orphan*/ * bitmap; int /*<<< orphan*/ * msi_groups; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPUHP_PCI_XGENE_DEAD ; 
 int /*<<< orphan*/  cpuhp_remove_state (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_xgene_online ; 
 struct xgene_msi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  xgene_free_domains (struct xgene_msi*) ; 

__attribute__((used)) static int xgene_msi_remove(struct platform_device *pdev)
{
	struct xgene_msi *msi = platform_get_drvdata(pdev);

	if (pci_xgene_online)
		cpuhp_remove_state(pci_xgene_online);
	cpuhp_remove_state(CPUHP_PCI_XGENE_DEAD);

	kfree(msi->msi_groups);

	kfree(msi->bitmap);
	msi->bitmap = NULL;

	xgene_free_domains(msi);

	return 0;
}