#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_hbq_init {int mask_count; int profile; TYPE_5__* hbqMasks; int /*<<< orphan*/  logEntry; int /*<<< orphan*/  headerLen; int /*<<< orphan*/  ring_mask; int /*<<< orphan*/  rn; int /*<<< orphan*/  entry_count; } ;
struct lpfc_hbq_entry {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  phys; } ;
struct lpfc_hba {TYPE_3__ hbqslimp; } ;
struct config_hbq_var {int hbqId; int numMask; int profile; TYPE_4__* hbqMasks; int /*<<< orphan*/  hbqaddrHigh; scalar_t__ hbqaddrLow; int /*<<< orphan*/  logEntry; int /*<<< orphan*/  headerLen; int /*<<< orphan*/  ringMask; int /*<<< orphan*/  recvNotify; int /*<<< orphan*/  entry_count; } ;
struct TYPE_11__ {struct config_hbq_var varCfgHbq; } ;
struct TYPE_15__ {int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; TYPE_2__ un; } ;
struct TYPE_10__ {TYPE_6__ mb; } ;
struct TYPE_16__ {TYPE_1__ u; } ;
struct TYPE_14__ {int /*<<< orphan*/  rctlmask; int /*<<< orphan*/  rctlmatch; int /*<<< orphan*/  tmask; int /*<<< orphan*/  tmatch; } ;
struct TYPE_13__ {int /*<<< orphan*/  rctlmask; int /*<<< orphan*/  rctlmatch; int /*<<< orphan*/  tmask; int /*<<< orphan*/  tmatch; } ;
typedef  TYPE_6__ MAILBOX_t ;
typedef  TYPE_7__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBX_CONFIG_HBQ ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  lpfc_build_hbq_profile2 (struct config_hbq_var*,struct lpfc_hbq_init*) ; 
 int /*<<< orphan*/  lpfc_build_hbq_profile3 (struct config_hbq_var*,struct lpfc_hbq_init*) ; 
 int /*<<< orphan*/  lpfc_build_hbq_profile5 (struct config_hbq_var*,struct lpfc_hbq_init*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putPaddrHigh (int /*<<< orphan*/ ) ; 
 scalar_t__ putPaddrLow (int /*<<< orphan*/ ) ; 

void
lpfc_config_hbq(struct lpfc_hba *phba, uint32_t id,
		 struct lpfc_hbq_init *hbq_desc,
		uint32_t hbq_entry_index, LPFC_MBOXQ_t *pmb)
{
	int i;
	MAILBOX_t *mb = &pmb->u.mb;
	struct config_hbq_var *hbqmb = &mb->un.varCfgHbq;

	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));
	hbqmb->hbqId = id;
	hbqmb->entry_count = hbq_desc->entry_count;   /* # entries in HBQ */
	hbqmb->recvNotify = hbq_desc->rn;             /* Receive
						       * Notification */
	hbqmb->numMask    = hbq_desc->mask_count;     /* # R_CTL/TYPE masks
						       * # in words 0-19 */
	hbqmb->profile    = hbq_desc->profile;	      /* Selection profile:
						       * 0 = all,
						       * 7 = logentry */
	hbqmb->ringMask   = hbq_desc->ring_mask;      /* Binds HBQ to a ring
						       * e.g. Ring0=b0001,
						       * ring2=b0100 */
	hbqmb->headerLen  = hbq_desc->headerLen;      /* 0 if not profile 4
						       * or 5 */
	hbqmb->logEntry   = hbq_desc->logEntry;       /* Set to 1 if this
						       * HBQ will be used
						       * for LogEntry
						       * buffers */
	hbqmb->hbqaddrLow = putPaddrLow(phba->hbqslimp.phys) +
		hbq_entry_index * sizeof(struct lpfc_hbq_entry);
	hbqmb->hbqaddrHigh = putPaddrHigh(phba->hbqslimp.phys);

	mb->mbxCommand = MBX_CONFIG_HBQ;
	mb->mbxOwner = OWN_HOST;

				/* Copy info for profiles 2,3,5. Other
				 * profiles this area is reserved
				 */
	if (hbq_desc->profile == 2)
		lpfc_build_hbq_profile2(hbqmb, hbq_desc);
	else if (hbq_desc->profile == 3)
		lpfc_build_hbq_profile3(hbqmb, hbq_desc);
	else if (hbq_desc->profile == 5)
		lpfc_build_hbq_profile5(hbqmb, hbq_desc);

	/* Return if no rctl / type masks for this HBQ */
	if (!hbq_desc->mask_count)
		return;

	/* Otherwise we setup specific rctl / type masks for this HBQ */
	for (i = 0; i < hbq_desc->mask_count; i++) {
		hbqmb->hbqMasks[i].tmatch = hbq_desc->hbqMasks[i].tmatch;
		hbqmb->hbqMasks[i].tmask  = hbq_desc->hbqMasks[i].tmask;
		hbqmb->hbqMasks[i].rctlmatch = hbq_desc->hbqMasks[i].rctlmatch;
		hbqmb->hbqMasks[i].rctlmask  = hbq_desc->hbqMasks[i].rctlmask;
	}

	return;
}