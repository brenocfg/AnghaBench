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
struct rtl8169_private {int mac_version; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChipCmd ; 
 int /*<<< orphan*/  CmdRxEnb ; 
#define  RTL_GIGA_MAC_VER_11 130 
#define  RTL_GIGA_MAC_VER_12 129 
#define  RTL_GIGA_MAC_VER_17 128 
 int /*<<< orphan*/  RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_wol_shutdown_quirk(struct rtl8169_private *tp)
{
	/* WoL fails with 8168b when the receiver is disabled. */
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_11:
	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
		pci_clear_master(tp->pci_dev);

		RTL_W8(tp, ChipCmd, CmdRxEnb);
		/* PCI commit */
		RTL_R8(tp, ChipCmd);
		break;
	default:
		break;
	}
}