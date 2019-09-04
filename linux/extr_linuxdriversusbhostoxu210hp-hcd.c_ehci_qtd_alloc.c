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
struct oxu_hcd {int* qtd_used; int /*<<< orphan*/  mem_lock; TYPE_1__* mem; } ;
struct ehci_qtd {int /*<<< orphan*/  qtd_dma; int /*<<< orphan*/  qtd_list; void* hw_alt_next; void* hw_next; int /*<<< orphan*/  hw_token; } ;
struct TYPE_2__ {int /*<<< orphan*/ * qtd_pool; } ;

/* Variables and functions */
 void* EHCI_LIST_END ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int QTD_NUM ; 
 int /*<<< orphan*/  QTD_STS_HALT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ehci_qtd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_phys (struct ehci_qtd*) ; 

__attribute__((used)) static struct ehci_qtd *ehci_qtd_alloc(struct oxu_hcd *oxu)
{
	int i;
	struct ehci_qtd *qtd = NULL;

	spin_lock(&oxu->mem_lock);

	for (i = 0; i < QTD_NUM; i++)
		if (!oxu->qtd_used[i])
			break;

	if (i < QTD_NUM) {
		qtd = (struct ehci_qtd *) &oxu->mem->qtd_pool[i];
		memset(qtd, 0, sizeof *qtd);

		qtd->hw_token = cpu_to_le32(QTD_STS_HALT);
		qtd->hw_next = EHCI_LIST_END;
		qtd->hw_alt_next = EHCI_LIST_END;
		INIT_LIST_HEAD(&qtd->qtd_list);

		qtd->qtd_dma = virt_to_phys(qtd);

		oxu->qtd_used[i] = 1;
	}

	spin_unlock(&oxu->mem_lock);

	return qtd;
}