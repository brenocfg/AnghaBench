#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  link_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int MBX_BUSY ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int MBX_SUCCESS ; 
 int /*<<< orphan*/  lpfc_down_link (struct lpfc_hba*,TYPE_1__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_hba_down_link(struct lpfc_hba *phba, uint32_t flag)
{
	LPFC_MBOXQ_t *pmb;
	int rc;

	pmb = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!pmb) {
		phba->link_state = LPFC_HBA_ERROR;
		return -ENOMEM;
	}

	lpfc_printf_log(phba,
		KERN_ERR, LOG_INIT,
		"0491 Adapter Link is disabled.\n");
	lpfc_down_link(phba, pmb);
	pmb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
	rc = lpfc_sli_issue_mbox(phba, pmb, flag);
	if ((rc != MBX_SUCCESS) && (rc != MBX_BUSY)) {
		lpfc_printf_log(phba,
		KERN_ERR, LOG_INIT,
		"2522 Adapter failed to issue DOWN_LINK"
		" mbox command rc 0x%x\n", rc);

		mempool_free(pmb, phba->mbox_mem_pool);
		return -EIO;
	}
	if (flag == MBX_POLL)
		mempool_free(pmb, phba->mbox_mem_pool);

	return 0;
}