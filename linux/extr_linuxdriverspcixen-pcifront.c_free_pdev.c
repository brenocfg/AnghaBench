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
struct pcifront_device {scalar_t__ irq; scalar_t__ evtchn; scalar_t__ gnt_ref; TYPE_1__* xdev; scalar_t__ sh_info; int /*<<< orphan*/  op_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ INVALID_EVTCHN ; 
 scalar_t__ INVALID_GRANT_REF ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct pcifront_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct pcifront_device*) ; 
 int /*<<< orphan*/  pcifront_free_roots (struct pcifront_device*) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (scalar_t__,struct pcifront_device*) ; 
 int /*<<< orphan*/  xenbus_free_evtchn (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void free_pdev(struct pcifront_device *pdev)
{
	dev_dbg(&pdev->xdev->dev, "freeing pdev @ 0x%p\n", pdev);

	pcifront_free_roots(pdev);

	cancel_work_sync(&pdev->op_work);

	if (pdev->irq >= 0)
		unbind_from_irqhandler(pdev->irq, pdev);

	if (pdev->evtchn != INVALID_EVTCHN)
		xenbus_free_evtchn(pdev->xdev, pdev->evtchn);

	if (pdev->gnt_ref != INVALID_GRANT_REF)
		gnttab_end_foreign_access(pdev->gnt_ref, 0 /* r/w page */,
					  (unsigned long)pdev->sh_info);
	else
		free_page((unsigned long)pdev->sh_info);

	dev_set_drvdata(&pdev->xdev->dev, NULL);

	kfree(pdev);
}