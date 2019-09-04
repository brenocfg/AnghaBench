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
struct rtl8169_private {int mac_version; int cp_cmd; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  event_slow; } ;

/* Variables and functions */
 int CPCMD_QUIRK_MASK ; 
 int /*<<< orphan*/  CPlusCmd ; 
 int /*<<< orphan*/  IntrMitigate ; 
 int /*<<< orphan*/  MaxTxPacketSize ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_NOSNOOP_EN ; 
#define  RTL_GIGA_MAC_VER_07 137 
#define  RTL_GIGA_MAC_VER_08 136 
#define  RTL_GIGA_MAC_VER_09 135 
 int RTL_GIGA_MAC_VER_13 ; 
 int RTL_GIGA_MAC_VER_16 ; 
#define  RTL_GIGA_MAC_VER_29 134 
#define  RTL_GIGA_MAC_VER_30 133 
#define  RTL_GIGA_MAC_VER_37 132 
#define  RTL_GIGA_MAC_VER_39 131 
#define  RTL_GIGA_MAC_VER_43 130 
#define  RTL_GIGA_MAC_VER_47 129 
#define  RTL_GIGA_MAC_VER_48 128 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RxFIFOOver ; 
 int /*<<< orphan*/  TxPacketMax ; 
 int /*<<< orphan*/  pcie_capability_set_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_hw_start_8102e_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8102e_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8102e_3 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8105e_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8105e_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8106 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168g_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168h_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8402 (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8101(struct rtl8169_private *tp)
{
	if (tp->mac_version >= RTL_GIGA_MAC_VER_30)
		tp->event_slow &= ~RxFIFOOver;

	if (tp->mac_version == RTL_GIGA_MAC_VER_13 ||
	    tp->mac_version == RTL_GIGA_MAC_VER_16)
		pcie_capability_set_word(tp->pci_dev, PCI_EXP_DEVCTL,
					 PCI_EXP_DEVCTL_NOSNOOP_EN);

	RTL_W8(tp, MaxTxPacketSize, TxPacketMax);

	tp->cp_cmd &= CPCMD_QUIRK_MASK;
	RTL_W16(tp, CPlusCmd, tp->cp_cmd);

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_07:
		rtl_hw_start_8102e_1(tp);
		break;

	case RTL_GIGA_MAC_VER_08:
		rtl_hw_start_8102e_3(tp);
		break;

	case RTL_GIGA_MAC_VER_09:
		rtl_hw_start_8102e_2(tp);
		break;

	case RTL_GIGA_MAC_VER_29:
		rtl_hw_start_8105e_1(tp);
		break;
	case RTL_GIGA_MAC_VER_30:
		rtl_hw_start_8105e_2(tp);
		break;

	case RTL_GIGA_MAC_VER_37:
		rtl_hw_start_8402(tp);
		break;

	case RTL_GIGA_MAC_VER_39:
		rtl_hw_start_8106(tp);
		break;
	case RTL_GIGA_MAC_VER_43:
		rtl_hw_start_8168g_2(tp);
		break;
	case RTL_GIGA_MAC_VER_47:
	case RTL_GIGA_MAC_VER_48:
		rtl_hw_start_8168h_1(tp);
		break;
	}

	RTL_W16(tp, IntrMitigate, 0x0000);
}