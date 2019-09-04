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
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int HT_3BIT_CAP_MASK ; 
 int HT_5BIT_CAP_MASK ; 
 int HT_CAPTYPE_HOST ; 
 int HT_CAPTYPE_SLAVE ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_CAP_ID_HT ; 
 int PCI_CAP_LIST_NEXT ; 
 int PCI_FIND_CAP_TTL ; 
 int __pci_find_next_cap_ttl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config_byte (struct pci_dev*,int,int*) ; 

__attribute__((used)) static int __pci_find_next_ht_cap(struct pci_dev *dev, int pos, int ht_cap)
{
	int rc, ttl = PCI_FIND_CAP_TTL;
	u8 cap, mask;

	if (ht_cap == HT_CAPTYPE_SLAVE || ht_cap == HT_CAPTYPE_HOST)
		mask = HT_3BIT_CAP_MASK;
	else
		mask = HT_5BIT_CAP_MASK;

	pos = __pci_find_next_cap_ttl(dev->bus, dev->devfn, pos,
				      PCI_CAP_ID_HT, &ttl);
	while (pos) {
		rc = pci_read_config_byte(dev, pos + 3, &cap);
		if (rc != PCIBIOS_SUCCESSFUL)
			return 0;

		if ((cap & mask) == ht_cap)
			return pos;

		pos = __pci_find_next_cap_ttl(dev->bus, dev->devfn,
					      pos + PCI_CAP_LIST_NEXT,
					      PCI_CAP_ID_HT, &ttl);
	}

	return 0;
}