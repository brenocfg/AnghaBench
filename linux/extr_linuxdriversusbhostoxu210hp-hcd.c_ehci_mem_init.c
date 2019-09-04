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
struct oxu_murb {int dummy; } ;
struct oxu_hcd {int periodic_size; int /*<<< orphan*/ * pshadow; void** periodic; int /*<<< orphan*/  periodic_dma; TYPE_1__* mem; int /*<<< orphan*/  async; scalar_t__* murb_used; void* murb_pool; scalar_t__* qtd_used; scalar_t__* qh_used; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  void* __le32 ;
struct TYPE_2__ {void** frame_list; } ;

/* Variables and functions */
 void* EHCI_LIST_END ; 
 int ENOMEM ; 
 int MURB_NUM ; 
 int QHEAD_NUM ; 
 int QTD_NUM ; 
 int /*<<< orphan*/  ehci_mem_cleanup (struct oxu_hcd*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxu_dbg (struct oxu_hcd*,char*) ; 
 int /*<<< orphan*/  oxu_qh_alloc (struct oxu_hcd*) ; 
 int /*<<< orphan*/  virt_to_phys (void**) ; 

__attribute__((used)) static int ehci_mem_init(struct oxu_hcd *oxu, gfp_t flags)
{
	int i;

	for (i = 0; i < oxu->periodic_size; i++)
		oxu->mem->frame_list[i] = EHCI_LIST_END;
	for (i = 0; i < QHEAD_NUM; i++)
		oxu->qh_used[i] = 0;
	for (i = 0; i < QTD_NUM; i++)
		oxu->qtd_used[i] = 0;

	oxu->murb_pool = kcalloc(MURB_NUM, sizeof(struct oxu_murb), flags);
	if (!oxu->murb_pool)
		goto fail;

	for (i = 0; i < MURB_NUM; i++)
		oxu->murb_used[i] = 0;

	oxu->async = oxu_qh_alloc(oxu);
	if (!oxu->async)
		goto fail;

	oxu->periodic = (__le32 *) &oxu->mem->frame_list;
	oxu->periodic_dma = virt_to_phys(oxu->periodic);

	for (i = 0; i < oxu->periodic_size; i++)
		oxu->periodic[i] = EHCI_LIST_END;

	/* software shadow of hardware table */
	oxu->pshadow = kcalloc(oxu->periodic_size, sizeof(void *), flags);
	if (oxu->pshadow != NULL)
		return 0;

fail:
	oxu_dbg(oxu, "couldn't init memory\n");
	ehci_mem_cleanup(oxu);
	return -ENOMEM;
}