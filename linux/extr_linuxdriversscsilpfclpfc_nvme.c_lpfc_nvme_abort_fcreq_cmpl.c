#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lpfc_wcqe_complete {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  abortIoTag; int /*<<< orphan*/  abortContextTag; } ;
struct TYPE_5__ {TYPE_1__ acxri; } ;
struct TYPE_6__ {TYPE_2__ un; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iotag; TYPE_3__ iocb; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,struct lpfc_wcqe_complete*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_wcqe_c_hw_status ; 
 int /*<<< orphan*/  lpfc_wcqe_c_request_tag ; 
 int /*<<< orphan*/  lpfc_wcqe_c_status ; 

void
lpfc_nvme_abort_fcreq_cmpl(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
			   struct lpfc_wcqe_complete *abts_cmpl)
{
	lpfc_printf_log(phba, KERN_INFO, LOG_NVME,
			"6145 ABORT_XRI_CN completing on rpi x%x "
			"original iotag x%x, abort cmd iotag x%x "
			"req_tag x%x, status x%x, hwstatus x%x\n",
			cmdiocb->iocb.un.acxri.abortContextTag,
			cmdiocb->iocb.un.acxri.abortIoTag,
			cmdiocb->iotag,
			bf_get(lpfc_wcqe_c_request_tag, abts_cmpl),
			bf_get(lpfc_wcqe_c_status, abts_cmpl),
			bf_get(lpfc_wcqe_c_hw_status, abts_cmpl));
	lpfc_sli_release_iocbq(phba, cmdiocb);
}