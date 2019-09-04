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
struct TYPE_4__ {int /*<<< orphan*/  numRiocb; } ;
struct TYPE_3__ {TYPE_2__ sli3; } ;
struct lpfc_sli_ring {size_t ringno; TYPE_1__ sli; } ;
struct lpfc_pgp {int /*<<< orphan*/  rspPutInx; } ;
struct lpfc_hba {int /*<<< orphan*/  work_hs; int /*<<< orphan*/  work_ha; int /*<<< orphan*/  link_state; struct lpfc_pgp* port_gp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HA_ERATT ; 
 int /*<<< orphan*/  HS_FFER3 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 

__attribute__((used)) static void
lpfc_sli_rsp_pointers_error(struct lpfc_hba *phba, struct lpfc_sli_ring *pring)
{
	struct lpfc_pgp *pgp = &phba->port_gp[pring->ringno];
	/*
	 * Ring <ringno> handler: portRspPut <portRspPut> is bigger than
	 * rsp ring <portRspMax>
	 */
	lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
			"0312 Ring %d handler: portRspPut %d "
			"is bigger than rsp ring %d\n",
			pring->ringno, le32_to_cpu(pgp->rspPutInx),
			pring->sli.sli3.numRiocb);

	phba->link_state = LPFC_HBA_ERROR;

	/*
	 * All error attention handlers are posted to
	 * worker thread
	 */
	phba->work_ha |= HA_ERATT;
	phba->work_hs = HS_FFER3;

	lpfc_worker_wake_up(phba);

	return;
}