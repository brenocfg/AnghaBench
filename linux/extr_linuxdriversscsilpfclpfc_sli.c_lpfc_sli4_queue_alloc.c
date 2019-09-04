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
typedef  union sli4_qe {int dummy; } sli4_qe ;
typedef  int uint32_t ;
struct lpfc_queue {int page_count; int entry_size; int entry_count; int page_size; int /*<<< orphan*/  spwork; int /*<<< orphan*/  irqwork; TYPE_4__* qe; int /*<<< orphan*/  page_list; struct lpfc_hba* phba; int /*<<< orphan*/  child_list; int /*<<< orphan*/  wqfull_list; int /*<<< orphan*/  wq_list; int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int if_page_sz; int wqpcnt; int /*<<< orphan*/  supported; } ;
struct TYPE_6__ {TYPE_1__ pc_sli4_params; } ;
struct lpfc_hba {TYPE_3__* pcidev; TYPE_2__ sli4_hba; } ;
struct lpfc_dmabuf {void* virt; int buffer_tag; int /*<<< orphan*/  list; int /*<<< orphan*/  phys; } ;
struct TYPE_8__ {void* address; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* dma_zalloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli4_hba_process_cq ; 
 int /*<<< orphan*/  lpfc_sli4_queue_free (struct lpfc_queue*) ; 
 int /*<<< orphan*/  lpfc_sli4_sp_process_cq ; 

struct lpfc_queue *
lpfc_sli4_queue_alloc(struct lpfc_hba *phba, uint32_t page_size,
		      uint32_t entry_size, uint32_t entry_count)
{
	struct lpfc_queue *queue;
	struct lpfc_dmabuf *dmabuf;
	int x, total_qe_count;
	void *dma_pointer;
	uint32_t hw_page_size = phba->sli4_hba.pc_sli4_params.if_page_sz;

	if (!phba->sli4_hba.pc_sli4_params.supported)
		hw_page_size = page_size;

	queue = kzalloc(sizeof(struct lpfc_queue) +
			(sizeof(union sli4_qe) * entry_count), GFP_KERNEL);
	if (!queue)
		return NULL;
	queue->page_count = (ALIGN(entry_size * entry_count,
			hw_page_size))/hw_page_size;

	/* If needed, Adjust page count to match the max the adapter supports */
	if (phba->sli4_hba.pc_sli4_params.wqpcnt &&
	    (queue->page_count > phba->sli4_hba.pc_sli4_params.wqpcnt))
		queue->page_count = phba->sli4_hba.pc_sli4_params.wqpcnt;

	INIT_LIST_HEAD(&queue->list);
	INIT_LIST_HEAD(&queue->wq_list);
	INIT_LIST_HEAD(&queue->wqfull_list);
	INIT_LIST_HEAD(&queue->page_list);
	INIT_LIST_HEAD(&queue->child_list);

	/* Set queue parameters now.  If the system cannot provide memory
	 * resources, the free routine needs to know what was allocated.
	 */
	queue->entry_size = entry_size;
	queue->entry_count = entry_count;
	queue->page_size = hw_page_size;
	queue->phba = phba;

	for (x = 0, total_qe_count = 0; x < queue->page_count; x++) {
		dmabuf = kzalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
		if (!dmabuf)
			goto out_fail;
		dmabuf->virt = dma_zalloc_coherent(&phba->pcidev->dev,
						   hw_page_size, &dmabuf->phys,
						   GFP_KERNEL);
		if (!dmabuf->virt) {
			kfree(dmabuf);
			goto out_fail;
		}
		dmabuf->buffer_tag = x;
		list_add_tail(&dmabuf->list, &queue->page_list);
		/* initialize queue's entry array */
		dma_pointer = dmabuf->virt;
		for (; total_qe_count < entry_count &&
		     dma_pointer < (hw_page_size + dmabuf->virt);
		     total_qe_count++, dma_pointer += entry_size) {
			queue->qe[total_qe_count].address = dma_pointer;
		}
	}
	INIT_WORK(&queue->irqwork, lpfc_sli4_hba_process_cq);
	INIT_WORK(&queue->spwork, lpfc_sli4_sp_process_cq);

	/* entry_repost will be set during q creation */

	return queue;
out_fail:
	lpfc_sli4_queue_free(queue);
	return NULL;
}