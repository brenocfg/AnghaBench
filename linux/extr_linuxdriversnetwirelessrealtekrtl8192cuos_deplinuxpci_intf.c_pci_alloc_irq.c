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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct dvobj_priv {int irq_alloc; struct pci_dev* ppcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  SA_SHIRQ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvobj_priv*) ; 
 int /*<<< orphan*/  rtw_pci_interrupt ; 

int pci_alloc_irq(struct dvobj_priv *dvobj)
{
	int err;
	struct pci_dev *pdev = dvobj->ppcidev;

#if defined(IRQF_SHARED)
	err = request_irq(pdev->irq, &rtw_pci_interrupt, IRQF_SHARED, DRV_NAME, dvobj);
#else
	err = request_irq(pdev->irq, &rtw_pci_interrupt, SA_SHIRQ, DRV_NAME, dvobj);
#endif
	if (err) {
		DBG_871X("Error allocating IRQ %d",pdev->irq);
	} else {
		dvobj->irq_alloc = 1;
		DBG_871X("Request_irq OK, IRQ %d\n",pdev->irq);
	}

	return err?_FAIL:_SUCCESS;
}