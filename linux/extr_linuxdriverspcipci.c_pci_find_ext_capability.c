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

/* Variables and functions */
 int pci_find_next_ext_capability (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

int pci_find_ext_capability(struct pci_dev *dev, int cap)
{
	return pci_find_next_ext_capability(dev, 0, cap);
}