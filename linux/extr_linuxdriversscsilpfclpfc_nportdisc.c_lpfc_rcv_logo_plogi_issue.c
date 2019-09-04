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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {TYPE_2__* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_rpi; } ;
struct TYPE_3__ {int /*<<< orphan*/  ulpIoTag; } ;
struct lpfc_iocbq {TYPE_1__ iocb; } ;
struct TYPE_4__ {scalar_t__ sli_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_LOGO ; 
 scalar_t__ LPFC_SLI_REV3 ; 
 int /*<<< orphan*/  lpfc_els_abort (TYPE_2__*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_rcv_logo (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_rcv_logo_plogi_issue(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  void *arg, uint32_t evt)
{
	struct lpfc_iocbq *cmdiocb = (struct lpfc_iocbq *) arg;

	/* Retrieve RPI from LOGO IOCB. RPI is used for CMD_ABORT_XRI_CN */
	if (vport->phba->sli_rev == LPFC_SLI_REV3)
		ndlp->nlp_rpi = cmdiocb->iocb.ulpIoTag;
				/* software abort outstanding PLOGI */
	lpfc_els_abort(vport->phba, ndlp);

	lpfc_rcv_logo(vport, ndlp, cmdiocb, ELS_CMD_LOGO);
	return ndlp->nlp_state;
}