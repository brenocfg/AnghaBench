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
typedef  union lpfc_wqe128 {int dummy; } lpfc_wqe128 ;
typedef  union lpfc_wqe {int dummy; } lpfc_wqe ;
typedef  scalar_t__ uint16_t ;
struct sli4_sge {int /*<<< orphan*/  word2; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_iocbq {struct lpfc_nvme_buf* context1; int /*<<< orphan*/  wqe_cmpl; int /*<<< orphan*/  iocb_flag; int /*<<< orphan*/  sli4_xritag; scalar_t__ sli4_lxritag; union lpfc_wqe128 wqe; } ;
struct lpfc_nvme_buf {int /*<<< orphan*/  list; struct lpfc_iocbq cur_iocbq; int /*<<< orphan*/  dma_phys_sgl; int /*<<< orphan*/  dma_handle; struct sli4_sge* nvme_sgl; struct sli4_sge* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  nvme_xri_cnt; int /*<<< orphan*/ * xri_ids; } ;
struct lpfc_hba {int cfg_sg_dma_buf_size; int /*<<< orphan*/  nvme_buf_list_get_lock; TYPE_1__ sli4_hba; int /*<<< orphan*/  lpfc_sg_dma_buf_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_NVME ; 
 int /*<<< orphan*/  LOG_NVME_IOERR ; 
 int /*<<< orphan*/  LPFC_IO_NVME ; 
 int /*<<< orphan*/  LPFC_SGE_TYPE_SKIP ; 
 scalar_t__ NO_XRI ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct sli4_sge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct sli4_sge*,int /*<<< orphan*/ ) ; 
 struct sli4_sge* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_nvme_buf*) ; 
 struct lpfc_nvme_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_nvme_io_cmd_wqe_cmpl ; 
 int lpfc_post_nvme_sgl_list (struct lpfc_hba*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  lpfc_sli4_free_xri (struct lpfc_hba*,scalar_t__) ; 
 scalar_t__ lpfc_sli4_next_xritag (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_sge_last ; 
 int /*<<< orphan*/  lpfc_sli4_sge_type ; 
 scalar_t__ lpfc_sli_next_iotag (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  memset (union lpfc_wqe128*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_nblist ; 
 int /*<<< orphan*/  post_nblist ; 
 int /*<<< orphan*/  prep_nblist ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_new_nvme_buf(struct lpfc_vport *vport, int num_to_alloc)
{
	struct lpfc_hba *phba = vport->phba;
	struct lpfc_nvme_buf *lpfc_ncmd;
	struct lpfc_iocbq *pwqeq;
	union lpfc_wqe128 *wqe;
	struct sli4_sge *sgl;
	dma_addr_t pdma_phys_sgl;
	uint16_t iotag, lxri = 0;
	int bcnt, num_posted, sgl_size;
	LIST_HEAD(prep_nblist);
	LIST_HEAD(post_nblist);
	LIST_HEAD(nvme_nblist);

	sgl_size = phba->cfg_sg_dma_buf_size;

	for (bcnt = 0; bcnt < num_to_alloc; bcnt++) {
		lpfc_ncmd = kzalloc(sizeof(struct lpfc_nvme_buf), GFP_KERNEL);
		if (!lpfc_ncmd)
			break;
		/*
		 * Get memory from the pci pool to map the virt space to
		 * pci bus space for an I/O. The DMA buffer includes the
		 * number of SGE's necessary to support the sg_tablesize.
		 */
		lpfc_ncmd->data = dma_pool_zalloc(phba->lpfc_sg_dma_buf_pool,
						  GFP_KERNEL,
						  &lpfc_ncmd->dma_handle);
		if (!lpfc_ncmd->data) {
			kfree(lpfc_ncmd);
			break;
		}

		lxri = lpfc_sli4_next_xritag(phba);
		if (lxri == NO_XRI) {
			dma_pool_free(phba->lpfc_sg_dma_buf_pool,
				      lpfc_ncmd->data, lpfc_ncmd->dma_handle);
			kfree(lpfc_ncmd);
			break;
		}
		pwqeq = &(lpfc_ncmd->cur_iocbq);
		wqe = &pwqeq->wqe;

		/* Allocate iotag for lpfc_ncmd->cur_iocbq. */
		iotag = lpfc_sli_next_iotag(phba, pwqeq);
		if (iotag == 0) {
			dma_pool_free(phba->lpfc_sg_dma_buf_pool,
				      lpfc_ncmd->data, lpfc_ncmd->dma_handle);
			kfree(lpfc_ncmd);
			lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
					"6121 Failed to allocated IOTAG for"
					" XRI:0x%x\n", lxri);
			lpfc_sli4_free_xri(phba, lxri);
			break;
		}
		pwqeq->sli4_lxritag = lxri;
		pwqeq->sli4_xritag = phba->sli4_hba.xri_ids[lxri];
		pwqeq->iocb_flag |= LPFC_IO_NVME;
		pwqeq->context1 = lpfc_ncmd;
		pwqeq->wqe_cmpl = lpfc_nvme_io_cmd_wqe_cmpl;

		/* Initialize local short-hand pointers. */
		lpfc_ncmd->nvme_sgl = lpfc_ncmd->data;
		sgl = lpfc_ncmd->nvme_sgl;
		pdma_phys_sgl = lpfc_ncmd->dma_handle;
		lpfc_ncmd->dma_phys_sgl = pdma_phys_sgl;

		/* Rsp SGE will be filled in when we rcv an IO
		 * from the NVME Layer to be sent.
		 * The cmd is going to be embedded so we need a SKIP SGE.
		 */
		bf_set(lpfc_sli4_sge_type, sgl, LPFC_SGE_TYPE_SKIP);
		bf_set(lpfc_sli4_sge_last, sgl, 0);
		sgl->word2 = cpu_to_le32(sgl->word2);
		/* Fill in word 3 / sgl_len during cmd submission */

		lpfc_ncmd->cur_iocbq.context1 = lpfc_ncmd;

		/* Initialize WQE */
		memset(wqe, 0, sizeof(union lpfc_wqe));

		/* add the nvme buffer to a post list */
		list_add_tail(&lpfc_ncmd->list, &post_nblist);
		spin_lock_irq(&phba->nvme_buf_list_get_lock);
		phba->sli4_hba.nvme_xri_cnt++;
		spin_unlock_irq(&phba->nvme_buf_list_get_lock);
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_NVME,
			"6114 Allocate %d out of %d requested new NVME "
			"buffers\n", bcnt, num_to_alloc);

	/* post the list of nvme buffer sgls to port if available */
	if (!list_empty(&post_nblist))
		num_posted = lpfc_post_nvme_sgl_list(phba,
						     &post_nblist, bcnt);
	else
		num_posted = 0;

	return num_posted;
}