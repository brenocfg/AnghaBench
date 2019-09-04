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
 int ENOMEM ; 
 int GASKET_NUM_BARS ; 
 int gasket_map_pci_bar (struct gasket_dev*,int) ; 
 int /*<<< orphan*/  gasket_unmap_pci_bar (struct gasket_dev*,int) ; 

__attribute__((used)) static int gasket_setup_pci(struct pci_dev *pci_dev,
			    struct gasket_dev *gasket_dev)
{
	int i, mapped_bars, ret;

	for (i = 0; i < GASKET_NUM_BARS; i++) {
		ret = gasket_map_pci_bar(gasket_dev, i);
		if (ret) {
			mapped_bars = i;
			goto fail;
		}
	}

	return 0;

fail:
	for (i = 0; i < mapped_bars; i++)
		gasket_unmap_pci_bar(gasket_dev, i);

	return -ENOMEM;
}