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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct xen_pci_sharedinfo {scalar_t__ flags; } ;
struct pcifront_device {int irq; struct xen_pci_sharedinfo* sh_info; int /*<<< orphan*/  op_work; int /*<<< orphan*/  gnt_ref; int /*<<< orphan*/  evtchn; int /*<<< orphan*/  sh_info_lock; int /*<<< orphan*/  root_buses; struct xenbus_device* xdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_EVTCHN ; 
 int /*<<< orphan*/  INVALID_GRANT_REF ; 
 int /*<<< orphan*/  _XEN_PCIB_AERHANDLER ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct pcifront_device*,struct xen_pci_sharedinfo*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct pcifront_device*) ; 
 int /*<<< orphan*/  kfree (struct pcifront_device*) ; 
 struct pcifront_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcifront_do_aer ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pcifront_device *alloc_pdev(struct xenbus_device *xdev)
{
	struct pcifront_device *pdev;

	pdev = kzalloc(sizeof(struct pcifront_device), GFP_KERNEL);
	if (pdev == NULL)
		goto out;

	pdev->sh_info =
	    (struct xen_pci_sharedinfo *)__get_free_page(GFP_KERNEL);
	if (pdev->sh_info == NULL) {
		kfree(pdev);
		pdev = NULL;
		goto out;
	}
	pdev->sh_info->flags = 0;

	/*Flag for registering PV AER handler*/
	set_bit(_XEN_PCIB_AERHANDLER, (void *)&pdev->sh_info->flags);

	dev_set_drvdata(&xdev->dev, pdev);
	pdev->xdev = xdev;

	INIT_LIST_HEAD(&pdev->root_buses);

	spin_lock_init(&pdev->sh_info_lock);

	pdev->evtchn = INVALID_EVTCHN;
	pdev->gnt_ref = INVALID_GRANT_REF;
	pdev->irq = -1;

	INIT_WORK(&pdev->op_work, pcifront_do_aer);

	dev_dbg(&xdev->dev, "Allocated pdev @ 0x%p pdev->sh_info @ 0x%p\n",
		pdev, pdev->sh_info);
out:
	return pdev;
}