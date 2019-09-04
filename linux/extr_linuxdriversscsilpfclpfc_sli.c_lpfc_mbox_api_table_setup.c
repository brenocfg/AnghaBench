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
typedef  int uint8_t ;
struct lpfc_hba {int /*<<< orphan*/  lpfc_sli_brdready; int /*<<< orphan*/  lpfc_sli_brdrestart; int /*<<< orphan*/  lpfc_sli_hbq_to_firmware; int /*<<< orphan*/  lpfc_sli_handle_slow_ring_event; int /*<<< orphan*/  lpfc_sli_issue_mbox; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_PCI_DEV_LP 129 
#define  LPFC_PCI_DEV_OC 128 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_sli_brdready_s3 ; 
 int /*<<< orphan*/  lpfc_sli_brdready_s4 ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart_s3 ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart_s4 ; 
 int /*<<< orphan*/  lpfc_sli_handle_slow_ring_event_s3 ; 
 int /*<<< orphan*/  lpfc_sli_handle_slow_ring_event_s4 ; 
 int /*<<< orphan*/  lpfc_sli_hbq_to_firmware_s3 ; 
 int /*<<< orphan*/  lpfc_sli_hbq_to_firmware_s4 ; 
 int /*<<< orphan*/  lpfc_sli_issue_mbox_s3 ; 
 int /*<<< orphan*/  lpfc_sli_issue_mbox_s4 ; 

int
lpfc_mbox_api_table_setup(struct lpfc_hba *phba, uint8_t dev_grp)
{

	switch (dev_grp) {
	case LPFC_PCI_DEV_LP:
		phba->lpfc_sli_issue_mbox = lpfc_sli_issue_mbox_s3;
		phba->lpfc_sli_handle_slow_ring_event =
				lpfc_sli_handle_slow_ring_event_s3;
		phba->lpfc_sli_hbq_to_firmware = lpfc_sli_hbq_to_firmware_s3;
		phba->lpfc_sli_brdrestart = lpfc_sli_brdrestart_s3;
		phba->lpfc_sli_brdready = lpfc_sli_brdready_s3;
		break;
	case LPFC_PCI_DEV_OC:
		phba->lpfc_sli_issue_mbox = lpfc_sli_issue_mbox_s4;
		phba->lpfc_sli_handle_slow_ring_event =
				lpfc_sli_handle_slow_ring_event_s4;
		phba->lpfc_sli_hbq_to_firmware = lpfc_sli_hbq_to_firmware_s4;
		phba->lpfc_sli_brdrestart = lpfc_sli_brdrestart_s4;
		phba->lpfc_sli_brdready = lpfc_sli_brdready_s4;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1420 Invalid HBA PCI-device group: 0x%x\n",
				dev_grp);
		return -ENODEV;
		break;
	}
	return 0;
}