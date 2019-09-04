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
struct pci_dev {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int inl (unsigned long) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 scalar_t__ pci_quatech_amcc (int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_quatech_init(struct pci_dev *dev)
{
	if (pci_quatech_amcc(dev->device)) {
		unsigned long base = pci_resource_start(dev, 0);
		if (base) {
			u32 tmp;

			outl(inl(base + 0x38) | 0x00002000, base + 0x38);
			tmp = inl(base + 0x3c);
			outl(tmp | 0x01000000, base + 0x3c);
			outl(tmp &= ~0x01000000, base + 0x3c);
		}
	}
	return 0;
}