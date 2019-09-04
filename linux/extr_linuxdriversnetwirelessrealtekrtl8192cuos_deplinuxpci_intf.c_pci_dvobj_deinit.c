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
struct dvobj_priv {scalar_t__ pci_mem_start; scalar_t__ irq_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  devobj_deinit (struct dvobj_priv*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dvobj_priv*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct dvobj_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,void*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_dvobj_deinit(struct pci_dev *pdev)
{
	struct dvobj_priv *dvobj = pci_get_drvdata(pdev);
_func_enter_;

	pci_set_drvdata(pdev, NULL);
	if (dvobj) {
		if (dvobj->irq_alloc) {
			free_irq(pdev->irq, dvobj);
			dvobj->irq_alloc = 0;
		}

		if (dvobj->pci_mem_start != 0) {
			pci_iounmap(pdev, (void *)dvobj->pci_mem_start);
			dvobj->pci_mem_start = 0;
		}

		devobj_deinit(dvobj);
	}

	pci_release_regions(pdev);
	pci_disable_device(pdev);

_func_exit_;
}