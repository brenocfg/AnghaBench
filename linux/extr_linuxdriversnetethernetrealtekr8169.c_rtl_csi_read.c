#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rtl8169_private {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIAR ; 
 int CSIAR_ADDR_MASK ; 
 int CSIAR_BYTE_ENABLE ; 
 int /*<<< orphan*/  CSIDR ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_csiar_cond ; 
 scalar_t__ rtl_udelay_loop_wait_high (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static u32 rtl_csi_read(struct rtl8169_private *tp, int addr)
{
	u32 func = PCI_FUNC(tp->pci_dev->devfn);

	RTL_W32(tp, CSIAR, (addr & CSIAR_ADDR_MASK) | func << 16 |
		CSIAR_BYTE_ENABLE);

	return rtl_udelay_loop_wait_high(tp, &rtl_csiar_cond, 10, 100) ?
		RTL_R32(tp, CSIDR) : ~0;
}