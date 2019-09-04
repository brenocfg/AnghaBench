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
struct xen_pcibk_config_quirk {int /*<<< orphan*/  quirks_list; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  kfree (struct xen_pcibk_config_quirk*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct xen_pcibk_config_quirk* xen_pcibk_find_quirk (struct pci_dev*) ; 

int xen_pcibk_config_quirk_release(struct pci_dev *dev)
{
	struct xen_pcibk_config_quirk *quirk;
	int ret = 0;

	quirk = xen_pcibk_find_quirk(dev);
	if (!quirk) {
		ret = -ENXIO;
		goto out;
	}

	list_del(&quirk->quirks_list);
	kfree(quirk);

out:
	return ret;
}