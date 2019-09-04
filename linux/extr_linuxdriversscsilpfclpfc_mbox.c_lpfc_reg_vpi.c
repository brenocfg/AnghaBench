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
struct lpfc_vport {int fc_flag; size_t vpi; size_t vfi; int /*<<< orphan*/  fc_portname; struct lpfc_hba* phba; int /*<<< orphan*/  fc_myDID; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_10__ {scalar_t__* vfi_ids; } ;
struct lpfc_hba {scalar_t__ sli_rev; scalar_t__ vfi_base; TYPE_2__ sli4_hba; int /*<<< orphan*/ * vpi_ids; } ;
struct TYPE_11__ {int upd; void** wwn; scalar_t__ vfi; int /*<<< orphan*/  sid; int /*<<< orphan*/  vpi; } ;
struct TYPE_12__ {TYPE_3__ varRegVpi; } ;
struct TYPE_13__ {int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; TYPE_4__ un; } ;
struct TYPE_9__ {TYPE_5__ mb; } ;
struct TYPE_14__ {TYPE_1__ u; } ;
typedef  TYPE_5__ MAILBOX_t ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_VPORT_NEEDS_REG_VPI ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  MBX_REG_VPI ; 
 int /*<<< orphan*/  OWN_HOST ; 
 void* cpu_to_le32 (void*) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_reg_vpi(struct lpfc_vport *vport, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	struct lpfc_hba *phba = vport->phba;

	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));
	/*
	 * Set the re-reg VPI bit for f/w to update the MAC address.
	 */
	if ((phba->sli_rev == LPFC_SLI_REV4) &&
		!(vport->fc_flag & FC_VPORT_NEEDS_REG_VPI))
		mb->un.varRegVpi.upd = 1;

	mb->un.varRegVpi.vpi = phba->vpi_ids[vport->vpi];
	mb->un.varRegVpi.sid = vport->fc_myDID;
	if (phba->sli_rev == LPFC_SLI_REV4)
		mb->un.varRegVpi.vfi = phba->sli4_hba.vfi_ids[vport->vfi];
	else
		mb->un.varRegVpi.vfi = vport->vfi + vport->phba->vfi_base;
	memcpy(mb->un.varRegVpi.wwn, &vport->fc_portname,
	       sizeof(struct lpfc_name));
	mb->un.varRegVpi.wwn[0] = cpu_to_le32(mb->un.varRegVpi.wwn[0]);
	mb->un.varRegVpi.wwn[1] = cpu_to_le32(mb->un.varRegVpi.wwn[1]);

	mb->mbxCommand = MBX_REG_VPI;
	mb->mbxOwner = OWN_HOST;
	return;

}