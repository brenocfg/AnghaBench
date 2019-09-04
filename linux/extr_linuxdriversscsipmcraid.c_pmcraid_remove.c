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
struct pmcraid_instance {int /*<<< orphan*/  host; int /*<<< orphan*/  mapped_dma_addr; int /*<<< orphan*/  worker_q; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pmcraid_instance* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pmcraid_disable_interrupts (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_kill_tasklets (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_release_buffers (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_release_chrdev (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_shutdown (struct pci_dev*) ; 
 int /*<<< orphan*/  pmcraid_unregister_interrupt_handler (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_remove(struct pci_dev *pdev)
{
	struct pmcraid_instance *pinstance = pci_get_drvdata(pdev);

	/* remove the management interface (/dev file) for this device */
	pmcraid_release_chrdev(pinstance);

	/* remove host template from scsi midlayer */
	scsi_remove_host(pinstance->host);

	/* block requests from mid-layer */
	scsi_block_requests(pinstance->host);

	/* initiate shutdown adapter */
	pmcraid_shutdown(pdev);

	pmcraid_disable_interrupts(pinstance, ~0);
	flush_work(&pinstance->worker_q);

	pmcraid_kill_tasklets(pinstance);
	pmcraid_unregister_interrupt_handler(pinstance);
	pmcraid_release_buffers(pinstance);
	iounmap(pinstance->mapped_dma_addr);
	pci_release_regions(pdev);
	scsi_host_put(pinstance->host);
	pci_disable_device(pdev);

	return;
}