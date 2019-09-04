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
struct lpfc_hba {int /*<<< orphan*/  hbalock; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __lpfc_mbuf_free (struct lpfc_hba*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
lpfc_mbuf_free(struct lpfc_hba * phba, void *virt, dma_addr_t dma)
{
	unsigned long iflags;

	spin_lock_irqsave(&phba->hbalock, iflags);
	__lpfc_mbuf_free(phba, virt, dma);
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	return;
}