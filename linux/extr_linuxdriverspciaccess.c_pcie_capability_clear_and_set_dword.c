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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int pcie_capability_read_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int pcie_capability_write_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

int pcie_capability_clear_and_set_dword(struct pci_dev *dev, int pos,
					u32 clear, u32 set)
{
	int ret;
	u32 val;

	ret = pcie_capability_read_dword(dev, pos, &val);
	if (!ret) {
		val &= ~clear;
		val |= set;
		ret = pcie_capability_write_dword(dev, pos, val);
	}

	return ret;
}