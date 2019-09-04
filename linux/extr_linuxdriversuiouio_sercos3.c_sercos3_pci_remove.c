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
struct uio_info {struct uio_info* priv; TYPE_1__* mem; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ internal_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct uio_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  uio_unregister_device (struct uio_info*) ; 

__attribute__((used)) static void sercos3_pci_remove(struct pci_dev *dev)
{
	struct uio_info *info = pci_get_drvdata(dev);
	int i;

	uio_unregister_device(info);
	pci_release_regions(dev);
	pci_disable_device(dev);
	for (i = 0; i < 5; i++) {
		if (info->mem[i].internal_addr)
			iounmap(info->mem[i].internal_addr);
	}
	kfree(info->priv);
	kfree(info);
}