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
struct ipr_ioa_cfg {int /*<<< orphan*/  host; int /*<<< orphan*/  hdw_dma_regs; scalar_t__ reset_work_q; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_free_irqs (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_free_mem (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_free_all_resources(struct ipr_ioa_cfg *ioa_cfg)
{
	struct pci_dev *pdev = ioa_cfg->pdev;

	ENTER;
	ipr_free_irqs(ioa_cfg);
	if (ioa_cfg->reset_work_q)
		destroy_workqueue(ioa_cfg->reset_work_q);
	iounmap(ioa_cfg->hdw_dma_regs);
	pci_release_regions(pdev);
	ipr_free_mem(ioa_cfg);
	scsi_host_put(ioa_cfg->host);
	pci_disable_device(pdev);
	LEAVE;
}