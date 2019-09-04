#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mvumi_hba {TYPE_2__* pdev; TYPE_1__* instancet; struct Scsi_Host* shost; int /*<<< orphan*/ * dm_thread; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_intr ) (struct mvumi_hba*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mvumi_hba*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvumi_detach_devices (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_flush_cache (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_release_fw (struct mvumi_hba*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct mvumi_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct mvumi_hba*) ; 

__attribute__((used)) static void mvumi_detach_one(struct pci_dev *pdev)
{
	struct Scsi_Host *host;
	struct mvumi_hba *mhba;

	mhba = pci_get_drvdata(pdev);
	if (mhba->dm_thread) {
		kthread_stop(mhba->dm_thread);
		mhba->dm_thread = NULL;
	}

	mvumi_detach_devices(mhba);
	host = mhba->shost;
	scsi_remove_host(mhba->shost);
	mvumi_flush_cache(mhba);

	mhba->instancet->disable_intr(mhba);
	free_irq(mhba->pdev->irq, mhba);
	mvumi_release_fw(mhba);
	scsi_host_put(host);
	pci_disable_device(pdev);
	dev_dbg(&pdev->dev, "driver is removed!\n");
}