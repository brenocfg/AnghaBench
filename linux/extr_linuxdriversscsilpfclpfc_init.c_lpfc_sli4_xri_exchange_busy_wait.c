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
struct TYPE_2__ {int /*<<< orphan*/  lpfc_abts_els_sgl_list; int /*<<< orphan*/  lpfc_abts_scsi_buf_list; int /*<<< orphan*/  lpfc_abts_nvmet_ctx_list; int /*<<< orphan*/  lpfc_abts_nvme_buf_list; } ;
struct lpfc_hba {int cfg_enable_fc4_type; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_ENABLE_FCP ; 
 int LPFC_ENABLE_NVME ; 
 int LPFC_XRI_EXCH_BUSY_WAIT_T1 ; 
 int LPFC_XRI_EXCH_BUSY_WAIT_T2 ; 
 int LPFC_XRI_EXCH_BUSY_WAIT_TMO ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_nvme_wait_for_io_drain (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void
lpfc_sli4_xri_exchange_busy_wait(struct lpfc_hba *phba)
{
	int wait_time = 0;
	int nvme_xri_cmpl = 1;
	int nvmet_xri_cmpl = 1;
	int fcp_xri_cmpl = 1;
	int els_xri_cmpl = list_empty(&phba->sli4_hba.lpfc_abts_els_sgl_list);

	/* Driver just aborted IOs during the hba_unset process.  Pause
	 * here to give the HBA time to complete the IO and get entries
	 * into the abts lists.
	 */
	msleep(LPFC_XRI_EXCH_BUSY_WAIT_T1 * 5);

	/* Wait for NVME pending IO to flush back to transport. */
	if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME)
		lpfc_nvme_wait_for_io_drain(phba);

	if (phba->cfg_enable_fc4_type & LPFC_ENABLE_FCP)
		fcp_xri_cmpl =
			list_empty(&phba->sli4_hba.lpfc_abts_scsi_buf_list);
	if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) {
		nvme_xri_cmpl =
			list_empty(&phba->sli4_hba.lpfc_abts_nvme_buf_list);
		nvmet_xri_cmpl =
			list_empty(&phba->sli4_hba.lpfc_abts_nvmet_ctx_list);
	}

	while (!fcp_xri_cmpl || !els_xri_cmpl || !nvme_xri_cmpl ||
	       !nvmet_xri_cmpl) {
		if (wait_time > LPFC_XRI_EXCH_BUSY_WAIT_TMO) {
			if (!nvmet_xri_cmpl)
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"6424 NVMET XRI exchange busy "
						"wait time: %d seconds.\n",
						wait_time/1000);
			if (!nvme_xri_cmpl)
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"6100 NVME XRI exchange busy "
						"wait time: %d seconds.\n",
						wait_time/1000);
			if (!fcp_xri_cmpl)
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"2877 FCP XRI exchange busy "
						"wait time: %d seconds.\n",
						wait_time/1000);
			if (!els_xri_cmpl)
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"2878 ELS XRI exchange busy "
						"wait time: %d seconds.\n",
						wait_time/1000);
			msleep(LPFC_XRI_EXCH_BUSY_WAIT_T2);
			wait_time += LPFC_XRI_EXCH_BUSY_WAIT_T2;
		} else {
			msleep(LPFC_XRI_EXCH_BUSY_WAIT_T1);
			wait_time += LPFC_XRI_EXCH_BUSY_WAIT_T1;
		}
		if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) {
			nvme_xri_cmpl = list_empty(
				&phba->sli4_hba.lpfc_abts_nvme_buf_list);
			nvmet_xri_cmpl = list_empty(
				&phba->sli4_hba.lpfc_abts_nvmet_ctx_list);
		}

		if (phba->cfg_enable_fc4_type & LPFC_ENABLE_FCP)
			fcp_xri_cmpl = list_empty(
				&phba->sli4_hba.lpfc_abts_scsi_buf_list);

		els_xri_cmpl =
			list_empty(&phba->sli4_hba.lpfc_abts_els_sgl_list);

	}
}