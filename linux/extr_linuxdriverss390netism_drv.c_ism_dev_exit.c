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
struct pci_dev {int dummy; } ;
struct ism_dev {int /*<<< orphan*/  smcd; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ism_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smcd_unregister_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_ieq (struct ism_dev*) ; 
 int /*<<< orphan*/  unregister_sba (struct ism_dev*) ; 

__attribute__((used)) static void ism_dev_exit(struct ism_dev *ism)
{
	struct pci_dev *pdev = ism->pdev;

	smcd_unregister_dev(ism->smcd);
	unregister_ieq(ism);
	unregister_sba(ism);
	free_irq(pci_irq_vector(pdev, 0), ism);
	pci_free_irq_vectors(pdev);
}