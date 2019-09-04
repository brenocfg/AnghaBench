#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lpfc_sli {int num_rings; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  link_state; struct lpfc_sli sli; } ;
struct TYPE_8__ {int /*<<< orphan*/  mbxStatus; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_7__ {TYPE_2__ mb; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ MAILBOX_t ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_INIT_MBX_CMDS ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int MBX_SUCCESS ; 
 int /*<<< orphan*/  lpfc_config_ring (struct lpfc_hba*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli_ring_map(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;
	LPFC_MBOXQ_t *pmb;
	MAILBOX_t *pmbox;
	int i, rc, ret = 0;

	pmb = (LPFC_MBOXQ_t *) mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!pmb)
		return -ENOMEM;
	pmbox = &pmb->u.mb;
	phba->link_state = LPFC_INIT_MBX_CMDS;
	for (i = 0; i < psli->num_rings; i++) {
		lpfc_config_ring(phba, i, pmb);
		rc = lpfc_sli_issue_mbox(phba, pmb, MBX_POLL);
		if (rc != MBX_SUCCESS) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0446 Adapter failed to init (%d), "
					"mbxCmd x%x CFG_RING, mbxStatus x%x, "
					"ring %d\n",
					rc, pmbox->mbxCommand,
					pmbox->mbxStatus, i);
			phba->link_state = LPFC_HBA_ERROR;
			ret = -ENXIO;
			break;
		}
	}
	mempool_free(pmb, phba->mbox_mem_pool);
	return ret;
}