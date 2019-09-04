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
struct intel_sst_drv {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 struct intel_sst_drv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_context_cleanup (struct intel_sst_drv*) ; 

__attribute__((used)) static void intel_sst_remove(struct pci_dev *pci)
{
	struct intel_sst_drv *sst_drv_ctx = pci_get_drvdata(pci);

	sst_context_cleanup(sst_drv_ctx);
	pci_dev_put(sst_drv_ctx->pci);
	pci_release_regions(pci);
	pci_set_drvdata(pci, NULL);
}