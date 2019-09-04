#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  vpi; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_usg_map; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_rpi; } ;
struct TYPE_9__ {int /*<<< orphan*/  sli_intf; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; TYPE_3__ sli4_hba; } ;
struct TYPE_7__ {scalar_t__ mbxCommand; } ;
struct TYPE_8__ {TYPE_1__ mb; } ;
struct TYPE_10__ {TYPE_2__ u; struct lpfc_nodelist* context1; struct lpfc_vport* vport; } ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ MBX_UNREG_LOGIN ; 
 int /*<<< orphan*/  NLP_LOGO_ACC ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  mempool_free (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
lpfc_sli4_unreg_rpi_cmpl_clr(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	struct lpfc_vport  *vport = pmb->vport;
	struct lpfc_nodelist *ndlp;

	ndlp = pmb->context1;
	if (pmb->u.mb.mbxCommand == MBX_UNREG_LOGIN) {
		if (phba->sli_rev == LPFC_SLI_REV4 &&
		    (bf_get(lpfc_sli_intf_if_type,
		     &phba->sli4_hba.sli_intf) >=
		     LPFC_SLI_INTF_IF_TYPE_2)) {
			if (ndlp) {
				lpfc_printf_vlog(vport, KERN_INFO, LOG_SLI,
						 "0010 UNREG_LOGIN vpi:%x "
						 "rpi:%x DID:%x map:%x %p\n",
						 vport->vpi, ndlp->nlp_rpi,
						 ndlp->nlp_DID,
						 ndlp->nlp_usg_map, ndlp);
				ndlp->nlp_flag &= ~NLP_LOGO_ACC;
				lpfc_nlp_put(ndlp);
			}
		}
	}

	mempool_free(pmb, phba->mbox_mem_pool);
}