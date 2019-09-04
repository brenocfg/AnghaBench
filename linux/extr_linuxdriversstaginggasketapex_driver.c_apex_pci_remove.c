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
struct gasket_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gasket_disable_device (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_pci_remove_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct gasket_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void apex_pci_remove(struct pci_dev *pci_dev)
{
	struct gasket_dev *gasket_dev = pci_get_drvdata(pci_dev);

	gasket_disable_device(gasket_dev);
	gasket_pci_remove_device(pci_dev);
	pci_disable_device(pci_dev);
}