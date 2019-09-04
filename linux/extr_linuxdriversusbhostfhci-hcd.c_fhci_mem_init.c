#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct td {int dummy; } ;
struct fhci_hcd {scalar_t__ active_urbs; TYPE_2__* process_done_task; int /*<<< orphan*/  empty_tds; int /*<<< orphan*/  empty_eds; void* vroot_hub; TYPE_1__* hc_list; } ;
struct ed {int dummy; } ;
struct TYPE_4__ {unsigned long data; } ;
struct TYPE_3__ {int /*<<< orphan*/  done_list; int /*<<< orphan*/  intr_list; int /*<<< orphan*/  iso_list; int /*<<< orphan*/  bulk_list; int /*<<< orphan*/  ctrl_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_EDS ; 
 int MAX_TDS ; 
 int /*<<< orphan*/  fhci_mem_free (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_recycle_empty_ed (struct fhci_hcd*,struct ed*) ; 
 int /*<<< orphan*/  fhci_recycle_empty_td (struct fhci_hcd*,struct td*) ; 
 TYPE_2__ fhci_tasklet ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fhci_mem_init(struct fhci_hcd *fhci)
{
	int i;

	fhci->hc_list = kzalloc(sizeof(*fhci->hc_list), GFP_KERNEL);
	if (!fhci->hc_list)
		goto err;

	INIT_LIST_HEAD(&fhci->hc_list->ctrl_list);
	INIT_LIST_HEAD(&fhci->hc_list->bulk_list);
	INIT_LIST_HEAD(&fhci->hc_list->iso_list);
	INIT_LIST_HEAD(&fhci->hc_list->intr_list);
	INIT_LIST_HEAD(&fhci->hc_list->done_list);

	fhci->vroot_hub = kzalloc(sizeof(*fhci->vroot_hub), GFP_KERNEL);
	if (!fhci->vroot_hub)
		goto err;

	INIT_LIST_HEAD(&fhci->empty_eds);
	INIT_LIST_HEAD(&fhci->empty_tds);

	/* initialize work queue to handle done list */
	fhci_tasklet.data = (unsigned long)fhci;
	fhci->process_done_task = &fhci_tasklet;

	for (i = 0; i < MAX_TDS; i++) {
		struct td *td;

		td = kmalloc(sizeof(*td), GFP_KERNEL);
		if (!td)
			goto err;
		fhci_recycle_empty_td(fhci, td);
	}
	for (i = 0; i < MAX_EDS; i++) {
		struct ed *ed;

		ed = kmalloc(sizeof(*ed), GFP_KERNEL);
		if (!ed)
			goto err;
		fhci_recycle_empty_ed(fhci, ed);
	}

	fhci->active_urbs = 0;
	return 0;
err:
	fhci_mem_free(fhci);
	return -ENOMEM;
}