#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  cfg_mhdr; } ;
struct lpfc_mbx_sli4_config {TYPE_4__ header; } ;
struct lpfc_mbx_sge {int /*<<< orphan*/  pa_lo; int /*<<< orphan*/  pa_hi; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; TYPE_5__* pcidev; } ;
struct TYPE_7__ {struct lpfc_mbx_sli4_config sli4_config; } ;
struct TYPE_8__ {TYPE_1__ un; } ;
struct TYPE_9__ {TYPE_2__ mqe; } ;
struct lpfcMboxq {TYPE_6__* sge_array; TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_PAGE_SIZE ; 
 size_t bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getPaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_emb ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_sge_cnt ; 
 int /*<<< orphan*/  lpfc_sli4_mbx_sge_get (struct lpfcMboxq*,size_t,struct lpfc_mbx_sge*) ; 
 int /*<<< orphan*/  mempool_free (struct lpfcMboxq*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void
lpfc_sli4_mbox_cmd_free(struct lpfc_hba *phba, struct lpfcMboxq *mbox)
{
	struct lpfc_mbx_sli4_config *sli4_cfg;
	struct lpfc_mbx_sge sge;
	dma_addr_t phyaddr;
	uint32_t sgecount, sgentry;

	sli4_cfg = &mbox->u.mqe.un.sli4_config;

	/* For embedded mbox command, just free the mbox command */
	if (bf_get(lpfc_mbox_hdr_emb, &sli4_cfg->header.cfg_mhdr)) {
		mempool_free(mbox, phba->mbox_mem_pool);
		return;
	}

	/* For non-embedded mbox command, we need to free the pages first */
	sgecount = bf_get(lpfc_mbox_hdr_sge_cnt, &sli4_cfg->header.cfg_mhdr);
	/* There is nothing we can do if there is no sge address array */
	if (unlikely(!mbox->sge_array)) {
		mempool_free(mbox, phba->mbox_mem_pool);
		return;
	}
	/* Each non-embedded DMA memory was allocated in the length of a page */
	for (sgentry = 0; sgentry < sgecount; sgentry++) {
		lpfc_sli4_mbx_sge_get(mbox, sgentry, &sge);
		phyaddr = getPaddr(sge.pa_hi, sge.pa_lo);
		dma_free_coherent(&phba->pcidev->dev, SLI4_PAGE_SIZE,
				  mbox->sge_array->addr[sgentry], phyaddr);
	}
	/* Free the sge address array memory */
	kfree(mbox->sge_array);
	/* Finally, free the mailbox command itself */
	mempool_free(mbox, phba->mbox_mem_pool);
}