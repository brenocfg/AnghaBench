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
struct bnx2fc_hba {int max_tasks; int /*<<< orphan*/ ** task_ctx_dma; int /*<<< orphan*/ ** task_ctx; TYPE_1__* pcidev; int /*<<< orphan*/ * task_ctx_bd_tbl; int /*<<< orphan*/ * task_ctx_bd_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2FC_TASKS_PER_PAGE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 

void bnx2fc_free_task_ctx(struct bnx2fc_hba *hba)
{
	int task_ctx_arr_sz;
	int i;

	if (hba->task_ctx_bd_tbl) {
		dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				    hba->task_ctx_bd_tbl,
				    hba->task_ctx_bd_dma);
		hba->task_ctx_bd_tbl = NULL;
	}

	task_ctx_arr_sz = (hba->max_tasks / BNX2FC_TASKS_PER_PAGE);
	if (hba->task_ctx) {
		for (i = 0; i < task_ctx_arr_sz; i++) {
			if (hba->task_ctx[i]) {
				dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
						    hba->task_ctx[i],
						    hba->task_ctx_dma[i]);
				hba->task_ctx[i] = NULL;
			}
		}
		kfree(hba->task_ctx);
		hba->task_ctx = NULL;
	}

	kfree(hba->task_ctx_dma);
	hba->task_ctx_dma = NULL;
}