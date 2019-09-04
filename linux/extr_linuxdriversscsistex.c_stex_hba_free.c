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
struct st_hba {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  dma_mem; int /*<<< orphan*/  dma_size; TYPE_1__* pdev; int /*<<< orphan*/  ccb; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  work_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_1__*) ; 
 int /*<<< orphan*/  stex_free_irq (struct st_hba*) ; 

__attribute__((used)) static void stex_hba_free(struct st_hba *hba)
{
	stex_free_irq(hba);

	destroy_workqueue(hba->work_q);

	iounmap(hba->mmio_base);

	pci_release_regions(hba->pdev);

	kfree(hba->ccb);

	dma_free_coherent(&hba->pdev->dev, hba->dma_size,
			  hba->dma_mem, hba->dma_handle);
}