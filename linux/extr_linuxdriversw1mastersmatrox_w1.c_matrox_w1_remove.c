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
struct matrox_device {int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  bus_master; scalar_t__ found; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct matrox_device*) ; 
 struct matrox_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  w1_remove_master_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void matrox_w1_remove(struct pci_dev *pdev)
{
	struct matrox_device *dev = pci_get_drvdata(pdev);

	if (dev->found) {
		w1_remove_master_device(dev->bus_master);
		iounmap(dev->virt_addr);
	}
	kfree(dev);
}