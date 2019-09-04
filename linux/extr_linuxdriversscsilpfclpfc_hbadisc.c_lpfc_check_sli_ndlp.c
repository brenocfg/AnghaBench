#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort ;
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_sli_ring {scalar_t__ ringno; } ;
struct lpfc_nodelist {int nlp_type; int nlp_flag; scalar_t__ nlp_rpi; int /*<<< orphan*/  nlp_DID; struct lpfc_vport* vport; } ;
struct TYPE_5__ {struct lpfc_nodelist* ndlp; } ;
struct TYPE_6__ {int /*<<< orphan*/  remoteID; } ;
struct TYPE_7__ {TYPE_2__ elsreq64; } ;
struct TYPE_8__ {int ulpCommand; scalar_t__ volatile ulpContext; TYPE_3__ un; } ;
struct lpfc_iocbq {int /*<<< orphan*/ * context1; TYPE_1__ context_un; struct lpfc_vport* vport; TYPE_4__ iocb; } ;
struct lpfc_hba {int dummy; } ;
typedef  TYPE_4__ IOCB_t ;

/* Variables and functions */
#define  CMD_ELS_REQUEST64_CR 130 
#define  CMD_GEN_REQUEST64_CR 129 
#define  CMD_XMIT_ELS_RSP64_CX 128 
 scalar_t__ LPFC_ELS_RING ; 
 scalar_t__ LPFC_FCP_RING ; 
 int NLP_DELAY_TMO ; 
 int NLP_FCP_TARGET ; 

int
lpfc_check_sli_ndlp(struct lpfc_hba *phba,
		    struct lpfc_sli_ring *pring,
		    struct lpfc_iocbq *iocb,
		    struct lpfc_nodelist *ndlp)
{
	IOCB_t *icmd = &iocb->iocb;
	struct lpfc_vport    *vport = ndlp->vport;

	if (iocb->vport != vport)
		return 0;

	if (pring->ringno == LPFC_ELS_RING) {
		switch (icmd->ulpCommand) {
		case CMD_GEN_REQUEST64_CR:
			if (iocb->context_un.ndlp == ndlp)
				return 1;
		case CMD_ELS_REQUEST64_CR:
			if (icmd->un.elsreq64.remoteID == ndlp->nlp_DID)
				return 1;
		case CMD_XMIT_ELS_RSP64_CX:
			if (iocb->context1 == (uint8_t *) ndlp)
				return 1;
		}
	} else if (pring->ringno == LPFC_FCP_RING) {
		/* Skip match check if waiting to relogin to FCP target */
		if ((ndlp->nlp_type & NLP_FCP_TARGET) &&
		    (ndlp->nlp_flag & NLP_DELAY_TMO)) {
			return 0;
		}
		if (icmd->ulpContext == (volatile ushort)ndlp->nlp_rpi) {
			return 1;
		}
	}
	return 0;
}