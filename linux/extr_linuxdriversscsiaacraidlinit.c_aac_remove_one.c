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
struct pci_dev {int dummy; } ;
struct aac_dev {int /*<<< orphan*/  entry; int /*<<< orphan*/  fsa_dev; int /*<<< orphan*/  fibs; int /*<<< orphan*/  queues; int /*<<< orphan*/  comm_phys; int /*<<< orphan*/  comm_addr; int /*<<< orphan*/  comm_size; TYPE_1__* pdev; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_CHARDEV_NEEDS_REINIT ; 
 int /*<<< orphan*/  __aac_shutdown (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_adapter_ioremap (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_cancel_safw_rescan_worker (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_cfg_major ; 
 int /*<<< orphan*/  aac_devices ; 
 int /*<<< orphan*/  aac_fib_map_free (struct aac_dev*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void aac_remove_one(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct aac_dev *aac = (struct aac_dev *)shost->hostdata;

	aac_cancel_safw_rescan_worker(aac);
	scsi_remove_host(shost);

	__aac_shutdown(aac);
	aac_fib_map_free(aac);
	dma_free_coherent(&aac->pdev->dev, aac->comm_size, aac->comm_addr,
			  aac->comm_phys);
	kfree(aac->queues);

	aac_adapter_ioremap(aac, 0);

	kfree(aac->fibs);
	kfree(aac->fsa_dev);

	list_del(&aac->entry);
	scsi_host_put(shost);
	pci_disable_device(pdev);
	if (list_empty(&aac_devices)) {
		unregister_chrdev(aac_cfg_major, "aac");
		aac_cfg_major = AAC_CHARDEV_NEEDS_REINIT;
	}
}