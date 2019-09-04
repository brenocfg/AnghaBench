#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_sli4_cfg_mhdr {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  req; } ;
struct lpfc_mbx_set_link_diag_state {TYPE_5__ u; } ;
struct TYPE_15__ {int lnk_tp; int lnk_no; } ;
struct TYPE_16__ {TYPE_3__ lnk_info; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; TYPE_4__ sli4_hba; } ;
struct TYPE_18__ {scalar_t__ mbxStatus; } ;
struct TYPE_13__ {struct lpfc_mbx_set_link_diag_state link_diag_state; } ;
struct TYPE_14__ {TYPE_1__ un; } ;
struct TYPE_19__ {TYPE_6__ mb; TYPE_2__ mqe; } ;
struct TYPE_20__ {TYPE_7__ u; } ;
typedef  TYPE_8__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int LPFC_DIAG_STATE_DIAG_BIT_VALID_CHANGE ; 
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_FCOE_LINK_DIAG_STATE ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_FCOE ; 
 int /*<<< orphan*/  LPFC_MBOX_TMO ; 
 int /*<<< orphan*/  LPFC_SLI4_MBX_EMBED ; 
 int MBX_SUCCESS ; 
 int MBX_TIMEOUT ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lpfc_mbx_set_diag_state_diag ; 
 int /*<<< orphan*/  lpfc_mbx_set_diag_state_diag_bit_valid ; 
 int /*<<< orphan*/  lpfc_mbx_set_diag_state_link_num ; 
 int /*<<< orphan*/  lpfc_mbx_set_diag_state_link_type ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int lpfc_sli4_config (struct lpfc_hba*,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox_wait (struct lpfc_hba*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_bsg_set_link_diag_state(struct lpfc_hba *phba, uint32_t diag)
{
	LPFC_MBOXQ_t *pmboxq;
	struct lpfc_mbx_set_link_diag_state *link_diag_state;
	uint32_t req_len, alloc_len;
	int mbxstatus = MBX_SUCCESS, rc;

	pmboxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!pmboxq)
		return -ENOMEM;

	req_len = (sizeof(struct lpfc_mbx_set_link_diag_state) -
		   sizeof(struct lpfc_sli4_cfg_mhdr));
	alloc_len = lpfc_sli4_config(phba, pmboxq, LPFC_MBOX_SUBSYSTEM_FCOE,
				LPFC_MBOX_OPCODE_FCOE_LINK_DIAG_STATE,
				req_len, LPFC_SLI4_MBX_EMBED);
	if (alloc_len != req_len) {
		rc = -ENOMEM;
		goto link_diag_state_set_out;
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
			"3128 Set link to diagnostic state:x%x (x%x/x%x)\n",
			diag, phba->sli4_hba.lnk_info.lnk_tp,
			phba->sli4_hba.lnk_info.lnk_no);

	link_diag_state = &pmboxq->u.mqe.un.link_diag_state;
	bf_set(lpfc_mbx_set_diag_state_diag_bit_valid, &link_diag_state->u.req,
	       LPFC_DIAG_STATE_DIAG_BIT_VALID_CHANGE);
	bf_set(lpfc_mbx_set_diag_state_link_num, &link_diag_state->u.req,
	       phba->sli4_hba.lnk_info.lnk_no);
	bf_set(lpfc_mbx_set_diag_state_link_type, &link_diag_state->u.req,
	       phba->sli4_hba.lnk_info.lnk_tp);
	if (diag)
		bf_set(lpfc_mbx_set_diag_state_diag,
		       &link_diag_state->u.req, 1);
	else
		bf_set(lpfc_mbx_set_diag_state_diag,
		       &link_diag_state->u.req, 0);

	mbxstatus = lpfc_sli_issue_mbox_wait(phba, pmboxq, LPFC_MBOX_TMO);

	if ((mbxstatus == MBX_SUCCESS) && (pmboxq->u.mb.mbxStatus == 0))
		rc = 0;
	else
		rc = -ENODEV;

link_diag_state_set_out:
	if (pmboxq && (mbxstatus != MBX_TIMEOUT))
		mempool_free(pmboxq, phba->mbox_mem_pool);

	return rc;
}