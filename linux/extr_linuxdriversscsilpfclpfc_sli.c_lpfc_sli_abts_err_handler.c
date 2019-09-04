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
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sub_ctxt_tag; } ;
struct TYPE_5__ {TYPE_1__ asyncstat; } ;
struct TYPE_6__ {int /*<<< orphan*/  ulpStatus; int /*<<< orphan*/  ulpContext; TYPE_2__ un; } ;
struct lpfc_iocbq {TYPE_3__ iocb; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 struct lpfc_vport* lpfc_find_vport_by_vpid (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_rpi (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lpfc_sli_abts_recover_port (struct lpfc_vport*,struct lpfc_nodelist*) ; 

__attribute__((used)) static void
lpfc_sli_abts_err_handler(struct lpfc_hba *phba,
			  struct lpfc_iocbq *iocbq)
{
	struct lpfc_nodelist *ndlp = NULL;
	uint16_t rpi = 0, vpi = 0;
	struct lpfc_vport *vport = NULL;

	/* The rpi in the ulpContext is vport-sensitive. */
	vpi = iocbq->iocb.un.asyncstat.sub_ctxt_tag;
	rpi = iocbq->iocb.ulpContext;

	lpfc_printf_log(phba, KERN_WARNING, LOG_SLI,
			"3092 Port generated ABTS async event "
			"on vpi %d rpi %d status 0x%x\n",
			vpi, rpi, iocbq->iocb.ulpStatus);

	vport = lpfc_find_vport_by_vpid(phba, vpi);
	if (!vport)
		goto err_exit;
	ndlp = lpfc_findnode_rpi(vport, rpi);
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp))
		goto err_exit;

	if (iocbq->iocb.ulpStatus == IOSTAT_LOCAL_REJECT)
		lpfc_sli_abts_recover_port(vport, ndlp);
	return;

 err_exit:
	lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
			"3095 Event Context not found, no "
			"action on vpi %d rpi %d status 0x%x, reason 0x%x\n",
			iocbq->iocb.ulpContext, iocbq->iocb.ulpStatus,
			vpi, rpi);
}