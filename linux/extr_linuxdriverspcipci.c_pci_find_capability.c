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
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  hdr_type; } ;

/* Variables and functions */
 int __pci_bus_find_cap_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __pci_find_next_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int pci_find_capability(struct pci_dev *dev, int cap)
{
	int pos;

	pos = __pci_bus_find_cap_start(dev->bus, dev->devfn, dev->hdr_type);
	if (pos)
		pos = __pci_find_next_cap(dev->bus, dev->devfn, pos, cap);

	return pos;
}