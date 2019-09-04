#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {int /*<<< orphan*/  vpi; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_login (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
lpfc_release_rpi(struct lpfc_hba *phba,
		struct lpfc_vport *vport,
		uint16_t rpi)
{
	LPFC_MBOXQ_t *pmb;
	int rc;

	pmb = (LPFC_MBOXQ_t *) mempool_alloc(phba->mbox_mem_pool,
			GFP_KERNEL);
	if (!pmb)
		lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
			"2796 mailbox memory allocation failed \n");
	else {
		lpfc_unreg_login(phba, vport->vpi, rpi, pmb);
		pmb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		rc = lpfc_sli_issue_mbox(phba, pmb, MBX_NOWAIT);
		if (rc == MBX_NOT_FINISHED)
			mempool_free(pmb, phba->mbox_mem_pool);
	}
}