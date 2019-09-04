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
struct pci_dev {scalar_t__ devfn; } ;
struct beiscsi_hba {int /*<<< orphan*/  shost; int /*<<< orphan*/  recover_port; int /*<<< orphan*/  hw_check; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_PCI_ERR ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  beiscsi_disable_port (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  beiscsi_session_fail ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_host_for_each_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static pci_ers_result_t beiscsi_eeh_err_detected(struct pci_dev *pdev,
		pci_channel_state_t state)
{
	struct beiscsi_hba *phba = NULL;

	phba = (struct beiscsi_hba *)pci_get_drvdata(pdev);
	set_bit(BEISCSI_HBA_PCI_ERR, &phba->state);

	beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
		    "BM_%d : EEH error detected\n");

	/* first stop UE detection when PCI error detected */
	del_timer_sync(&phba->hw_check);
	cancel_delayed_work_sync(&phba->recover_port);

	/* sessions are no longer valid, so first fail the sessions */
	iscsi_host_for_each_session(phba->shost, beiscsi_session_fail);
	beiscsi_disable_port(phba, 0);

	if (state == pci_channel_io_perm_failure) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : EEH : State PERM Failure");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	pci_disable_device(pdev);

	/* The error could cause the FW to trigger a flash debug dump.
	 * Resetting the card while flash dump is in progress
	 * can cause it not to recover; wait for it to finish.
	 * Wait only for first function as it is needed only once per
	 * adapter.
	 **/
	if (pdev->devfn == 0)
		ssleep(30);

	return PCI_ERS_RESULT_NEED_RESET;
}