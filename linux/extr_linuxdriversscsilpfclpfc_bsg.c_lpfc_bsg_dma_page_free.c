#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lpfc_hba {struct pci_dev* pcidev; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; scalar_t__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSG_MBOX_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 

__attribute__((used)) static void
lpfc_bsg_dma_page_free(struct lpfc_hba *phba, struct lpfc_dmabuf *dmabuf)
{
	struct pci_dev *pcidev = phba->pcidev;

	if (!dmabuf)
		return;

	if (dmabuf->virt)
		dma_free_coherent(&pcidev->dev, BSG_MBOX_SIZE,
				  dmabuf->virt, dmabuf->phys);
	kfree(dmabuf);
	return;
}