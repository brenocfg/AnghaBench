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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 pci_hdr_type(struct pci_dev *dev)
{
	u8 hdr_type;

#ifdef CONFIG_PCI_IOV
	if (dev->is_virtfn)
		return dev->physfn->sriov->hdr_type;
#endif
	pci_read_config_byte(dev, PCI_HEADER_TYPE, &hdr_type);
	return hdr_type;
}