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
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static void quirk_amd_ordering(struct pci_dev *dev)
{
	u32 pcic;
	pci_read_config_dword(dev, 0x4C, &pcic);
	if ((pcic & 6) != 6) {
		pcic |= 6;
		pci_warn(dev, "BIOS failed to enable PCI standards compliance; fixing this error\n");
		pci_write_config_dword(dev, 0x4C, pcic);
		pci_read_config_dword(dev, 0x84, &pcic);
		pcic |= (1 << 23);	/* Required in this mode */
		pci_write_config_dword(dev, 0x84, pcic);
	}
}