#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpfc_mbox_ext_buf_ctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  ext_dmabuf_list; int /*<<< orphan*/  mbx_dmabuf; } ;
struct lpfc_hba {TYPE_1__ mbox_ext_buf_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ LPFC_BSG_MBOX_IDLE ; 
 int /*<<< orphan*/  lpfc_bsg_dma_page_free (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_bsg_dma_page_list_free (struct lpfc_hba*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lpfc_bsg_mbox_ext_session_reset(struct lpfc_hba *phba)
{
	if (phba->mbox_ext_buf_ctx.state == LPFC_BSG_MBOX_IDLE)
		return;

	/* free all memory, including dma buffers */
	lpfc_bsg_dma_page_list_free(phba,
				    &phba->mbox_ext_buf_ctx.ext_dmabuf_list);
	lpfc_bsg_dma_page_free(phba, phba->mbox_ext_buf_ctx.mbx_dmabuf);
	/* multi-buffer write mailbox command pass-through complete */
	memset((char *)&phba->mbox_ext_buf_ctx, 0,
	       sizeof(struct lpfc_mbox_ext_buf_ctx));
	INIT_LIST_HEAD(&phba->mbox_ext_buf_ctx.ext_dmabuf_list);

	return;
}