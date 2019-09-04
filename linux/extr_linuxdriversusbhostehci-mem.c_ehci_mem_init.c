#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ehci_sitd {int dummy; } ;
struct ehci_qtd {int dummy; } ;
struct ehci_qh_hw {void* hw_alt_next; void* hw_qtd_next; void* hw_next; } ;
struct ehci_itd {int dummy; } ;
struct ehci_hcd {int periodic_size; int /*<<< orphan*/ * pshadow; void** periodic; TYPE_2__* dummy; scalar_t__ use_dummy_qh; int /*<<< orphan*/  periodic_dma; void* sitd_pool; void* itd_pool; void* async; void* qh_pool; void* qtd_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  void* __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  sysdev; } ;
struct TYPE_6__ {TYPE_1__ self; } ;
struct TYPE_5__ {int /*<<< orphan*/  qh_dma; struct ehci_qh_hw* hw; } ;

/* Variables and functions */
 void* EHCI_LIST_END (struct ehci_hcd*) ; 
 int ENOMEM ; 
 void* cpu_to_hc32 (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/  ehci_mem_cleanup (struct ehci_hcd*) ; 
 void* ehci_qh_alloc (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehci_mem_init (struct ehci_hcd *ehci, gfp_t flags)
{
	int i;

	/* QTDs for control/bulk/intr transfers */
	ehci->qtd_pool = dma_pool_create ("ehci_qtd",
			ehci_to_hcd(ehci)->self.sysdev,
			sizeof (struct ehci_qtd),
			32 /* byte alignment (for hw parts) */,
			4096 /* can't cross 4K */);
	if (!ehci->qtd_pool) {
		goto fail;
	}

	/* QHs for control/bulk/intr transfers */
	ehci->qh_pool = dma_pool_create ("ehci_qh",
			ehci_to_hcd(ehci)->self.sysdev,
			sizeof(struct ehci_qh_hw),
			32 /* byte alignment (for hw parts) */,
			4096 /* can't cross 4K */);
	if (!ehci->qh_pool) {
		goto fail;
	}
	ehci->async = ehci_qh_alloc (ehci, flags);
	if (!ehci->async) {
		goto fail;
	}

	/* ITD for high speed ISO transfers */
	ehci->itd_pool = dma_pool_create ("ehci_itd",
			ehci_to_hcd(ehci)->self.sysdev,
			sizeof (struct ehci_itd),
			32 /* byte alignment (for hw parts) */,
			4096 /* can't cross 4K */);
	if (!ehci->itd_pool) {
		goto fail;
	}

	/* SITD for full/low speed split ISO transfers */
	ehci->sitd_pool = dma_pool_create ("ehci_sitd",
			ehci_to_hcd(ehci)->self.sysdev,
			sizeof (struct ehci_sitd),
			32 /* byte alignment (for hw parts) */,
			4096 /* can't cross 4K */);
	if (!ehci->sitd_pool) {
		goto fail;
	}

	/* Hardware periodic table */
	ehci->periodic = (__le32 *)
		dma_alloc_coherent(ehci_to_hcd(ehci)->self.sysdev,
			ehci->periodic_size * sizeof(__le32),
			&ehci->periodic_dma, flags);
	if (ehci->periodic == NULL) {
		goto fail;
	}

	if (ehci->use_dummy_qh) {
		struct ehci_qh_hw	*hw;
		ehci->dummy = ehci_qh_alloc(ehci, flags);
		if (!ehci->dummy)
			goto fail;

		hw = ehci->dummy->hw;
		hw->hw_next = EHCI_LIST_END(ehci);
		hw->hw_qtd_next = EHCI_LIST_END(ehci);
		hw->hw_alt_next = EHCI_LIST_END(ehci);
		ehci->dummy->hw = hw;

		for (i = 0; i < ehci->periodic_size; i++)
			ehci->periodic[i] = cpu_to_hc32(ehci,
					ehci->dummy->qh_dma);
	} else {
		for (i = 0; i < ehci->periodic_size; i++)
			ehci->periodic[i] = EHCI_LIST_END(ehci);
	}

	/* software shadow of hardware table */
	ehci->pshadow = kcalloc(ehci->periodic_size, sizeof(void *), flags);
	if (ehci->pshadow != NULL)
		return 0;

fail:
	ehci_dbg (ehci, "couldn't init memory\n");
	ehci_mem_cleanup (ehci);
	return -ENOMEM;
}