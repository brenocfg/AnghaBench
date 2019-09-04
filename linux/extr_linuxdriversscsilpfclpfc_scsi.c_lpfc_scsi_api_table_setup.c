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
struct lpfc_hba {int /*<<< orphan*/  lpfc_scsi_cmd_iocb_cmpl; int /*<<< orphan*/  lpfc_rampdown_queue_depth; int /*<<< orphan*/  lpfc_get_scsi_buf; int /*<<< orphan*/  lpfc_release_scsi_buf; int /*<<< orphan*/  lpfc_bg_scsi_prep_dma_buf; int /*<<< orphan*/  lpfc_scsi_prep_dma_buf; int /*<<< orphan*/  lpfc_new_scsi_buf; int /*<<< orphan*/  lpfc_scsi_prep_cmnd; int /*<<< orphan*/  lpfc_scsi_unprep_dma_buf; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_PCI_DEV_LP 129 
#define  LPFC_PCI_DEV_OC 128 
 int /*<<< orphan*/  lpfc_bg_scsi_prep_dma_buf_s3 ; 
 int /*<<< orphan*/  lpfc_bg_scsi_prep_dma_buf_s4 ; 
 int /*<<< orphan*/  lpfc_get_scsi_buf_s3 ; 
 int /*<<< orphan*/  lpfc_get_scsi_buf_s4 ; 
 int /*<<< orphan*/  lpfc_new_scsi_buf_s3 ; 
 int /*<<< orphan*/  lpfc_new_scsi_buf_s4 ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_rampdown_queue_depth ; 
 int /*<<< orphan*/  lpfc_release_scsi_buf_s3 ; 
 int /*<<< orphan*/  lpfc_release_scsi_buf_s4 ; 
 int /*<<< orphan*/  lpfc_scsi_cmd_iocb_cmpl ; 
 int /*<<< orphan*/  lpfc_scsi_prep_cmnd ; 
 int /*<<< orphan*/  lpfc_scsi_prep_dma_buf_s3 ; 
 int /*<<< orphan*/  lpfc_scsi_prep_dma_buf_s4 ; 
 int /*<<< orphan*/  lpfc_scsi_unprep_dma_buf ; 

int
lpfc_scsi_api_table_setup(struct lpfc_hba *phba, uint8_t dev_grp)
{

	phba->lpfc_scsi_unprep_dma_buf = lpfc_scsi_unprep_dma_buf;
	phba->lpfc_scsi_prep_cmnd = lpfc_scsi_prep_cmnd;

	switch (dev_grp) {
	case LPFC_PCI_DEV_LP:
		phba->lpfc_new_scsi_buf = lpfc_new_scsi_buf_s3;
		phba->lpfc_scsi_prep_dma_buf = lpfc_scsi_prep_dma_buf_s3;
		phba->lpfc_bg_scsi_prep_dma_buf = lpfc_bg_scsi_prep_dma_buf_s3;
		phba->lpfc_release_scsi_buf = lpfc_release_scsi_buf_s3;
		phba->lpfc_get_scsi_buf = lpfc_get_scsi_buf_s3;
		break;
	case LPFC_PCI_DEV_OC:
		phba->lpfc_new_scsi_buf = lpfc_new_scsi_buf_s4;
		phba->lpfc_scsi_prep_dma_buf = lpfc_scsi_prep_dma_buf_s4;
		phba->lpfc_bg_scsi_prep_dma_buf = lpfc_bg_scsi_prep_dma_buf_s4;
		phba->lpfc_release_scsi_buf = lpfc_release_scsi_buf_s4;
		phba->lpfc_get_scsi_buf = lpfc_get_scsi_buf_s4;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1418 Invalid HBA PCI-device group: 0x%x\n",
				dev_grp);
		return -ENODEV;
		break;
	}
	phba->lpfc_rampdown_queue_depth = lpfc_rampdown_queue_depth;
	phba->lpfc_scsi_cmd_iocb_cmpl = lpfc_scsi_cmd_iocb_cmpl;
	return 0;
}