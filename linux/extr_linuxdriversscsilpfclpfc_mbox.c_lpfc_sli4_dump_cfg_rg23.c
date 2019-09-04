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
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  list; struct lpfcMboxq* virt; } ;
struct TYPE_6__ {int /*<<< orphan*/  sli4_length; int /*<<< orphan*/  region_id; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/ * varWords; TYPE_2__ varDmp; } ;
struct TYPE_8__ {TYPE_3__ un; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_5__ {TYPE_4__ mb; } ;
struct lpfcMboxq {int /*<<< orphan*/ * context1; TYPE_1__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMP_NV_PARAMS ; 
 int /*<<< orphan*/  DMP_REGION_23 ; 
 int /*<<< orphan*/  DMP_RGN23_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 int LPFC_BPL_SIZE ; 
 int /*<<< orphan*/  MBX_DUMP_MEMORY ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct lpfcMboxq* lpfc_mbuf_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct lpfcMboxq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putPaddrHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putPaddrLow (int /*<<< orphan*/ ) ; 

int
lpfc_sli4_dump_cfg_rg23(struct lpfc_hba *phba, struct lpfcMboxq *mbox)
{
	struct lpfc_dmabuf *mp = NULL;
	MAILBOX_t *mb;

	memset(mbox, 0, sizeof(*mbox));
	mb = &mbox->u.mb;

	mp = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (mp)
		mp->virt = lpfc_mbuf_alloc(phba, 0, &mp->phys);

	if (!mp || !mp->virt) {
		kfree(mp);
		/* dump config region 23 failed to allocate memory */
		lpfc_printf_log(phba, KERN_WARNING, LOG_MBOX,
			"2569 lpfc dump config region 23: memory"
			" allocation failed\n");
		return 1;
	}

	memset(mp->virt, 0, LPFC_BPL_SIZE);
	INIT_LIST_HEAD(&mp->list);

	/* save address for completion */
	mbox->context1 = (uint8_t *) mp;

	mb->mbxCommand = MBX_DUMP_MEMORY;
	mb->un.varDmp.type = DMP_NV_PARAMS;
	mb->un.varDmp.region_id = DMP_REGION_23;
	mb->un.varDmp.sli4_length = DMP_RGN23_SIZE;
	mb->un.varWords[3] = putPaddrLow(mp->phys);
	mb->un.varWords[4] = putPaddrHigh(mp->phys);
	return 0;
}