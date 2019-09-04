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
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int /*<<< orphan*/  worker_thread; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_MBX_WAIT ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli_disable_intr (struct lpfc_hba*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_pci_suspend_one_s3(struct pci_dev *pdev, pm_message_t msg)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"0473 PCI device Power Management suspend.\n");

	/* Bring down the device */
	lpfc_offline_prep(phba, LPFC_MBX_WAIT);
	lpfc_offline(phba);
	kthread_stop(phba->worker_thread);

	/* Disable interrupt from device */
	lpfc_sli_disable_intr(phba);

	/* Save device state to PCI config space */
	pci_save_state(pdev);
	pci_set_power_state(pdev, PCI_D3hot);

	return 0;
}