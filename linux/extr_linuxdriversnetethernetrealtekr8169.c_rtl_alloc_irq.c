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
struct rtl8169_private {scalar_t__ mac_version; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cfg9346 ; 
 int Cfg9346_Lock ; 
 int Cfg9346_Unlock ; 
 int /*<<< orphan*/  Config2 ; 
 int MSIEnable ; 
 unsigned int PCI_IRQ_ALL_TYPES ; 
 unsigned int PCI_IRQ_LEGACY ; 
 scalar_t__ RTL_GIGA_MAC_VER_06 ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static int rtl_alloc_irq(struct rtl8169_private *tp)
{
	unsigned int flags;

	if (tp->mac_version <= RTL_GIGA_MAC_VER_06) {
		RTL_W8(tp, Cfg9346, Cfg9346_Unlock);
		RTL_W8(tp, Config2, RTL_R8(tp, Config2) & ~MSIEnable);
		RTL_W8(tp, Cfg9346, Cfg9346_Lock);
		flags = PCI_IRQ_LEGACY;
	} else {
		flags = PCI_IRQ_ALL_TYPES;
	}

	return pci_alloc_irq_vectors(tp->pci_dev, 1, 1, flags);
}