#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  fc_myDID; } ;
struct TYPE_10__ {int /*<<< orphan*/  bbscn_params; } ;
struct lpfc_hba {scalar_t__ sli_rev; scalar_t__ cfg_ack0; TYPE_2__ sli4_hba; scalar_t__ cfg_enable_bbcr; scalar_t__ bbcredit_support; int /*<<< orphan*/  fc_crtov; int /*<<< orphan*/  fc_altov; int /*<<< orphan*/  fc_rttov; int /*<<< orphan*/  fc_ratov; int /*<<< orphan*/  fc_arbtov; int /*<<< orphan*/  fc_edtov; int /*<<< orphan*/  cfg_cr_count; scalar_t__ cfg_cr_delay; struct lpfc_vport* pport; } ;
struct TYPE_11__ {int cr; int ci; int cscn; int ack0_enable; int /*<<< orphan*/  bbscn; int /*<<< orphan*/  crtov; int /*<<< orphan*/  altov; int /*<<< orphan*/  rttov; int /*<<< orphan*/  ratov; int /*<<< orphan*/  arbtov; int /*<<< orphan*/  edtov; int /*<<< orphan*/  myId; int /*<<< orphan*/  cr_count; scalar_t__ cr_delay; } ;
struct TYPE_12__ {TYPE_3__ varCfgLnk; } ;
struct TYPE_13__ {int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; TYPE_4__ un; } ;
struct TYPE_9__ {TYPE_5__ mb; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
typedef  TYPE_5__ MAILBOX_t ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  MBX_CONFIG_LINK ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_bbscn_def ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_config_link(struct lpfc_hba * phba, LPFC_MBOXQ_t * pmb)
{
	struct lpfc_vport  *vport = phba->pport;
	MAILBOX_t *mb = &pmb->u.mb;
	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));

	/* NEW_FEATURE
	 * SLI-2, Coalescing Response Feature.
	 */
	if (phba->cfg_cr_delay && (phba->sli_rev < LPFC_SLI_REV4)) {
		mb->un.varCfgLnk.cr = 1;
		mb->un.varCfgLnk.ci = 1;
		mb->un.varCfgLnk.cr_delay = phba->cfg_cr_delay;
		mb->un.varCfgLnk.cr_count = phba->cfg_cr_count;
	}

	mb->un.varCfgLnk.myId = vport->fc_myDID;
	mb->un.varCfgLnk.edtov = phba->fc_edtov;
	mb->un.varCfgLnk.arbtov = phba->fc_arbtov;
	mb->un.varCfgLnk.ratov = phba->fc_ratov;
	mb->un.varCfgLnk.rttov = phba->fc_rttov;
	mb->un.varCfgLnk.altov = phba->fc_altov;
	mb->un.varCfgLnk.crtov = phba->fc_crtov;
	mb->un.varCfgLnk.cscn = 0;
	if (phba->bbcredit_support && phba->cfg_enable_bbcr) {
		mb->un.varCfgLnk.cscn = 1;
		mb->un.varCfgLnk.bbscn = bf_get(lpfc_bbscn_def,
						 &phba->sli4_hba.bbscn_params);
	}

	if (phba->cfg_ack0 && (phba->sli_rev < LPFC_SLI_REV4))
		mb->un.varCfgLnk.ack0_enable = 1;

	mb->mbxCommand = MBX_CONFIG_LINK;
	mb->mbxOwner = OWN_HOST;
	return;
}