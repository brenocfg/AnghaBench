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
struct rtl8169_private {int cp_cmd; int mac_version; int event_slow; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPlusCmd ; 
 int INTT_1 ; 
 int INTT_MASK ; 
 int /*<<< orphan*/  IntrMitigate ; 
 int /*<<< orphan*/  MaxTxPacketSize ; 
 int PCSTimeout ; 
 int PktCntrDisable ; 
#define  RTL_GIGA_MAC_VER_11 157 
#define  RTL_GIGA_MAC_VER_12 156 
#define  RTL_GIGA_MAC_VER_17 155 
#define  RTL_GIGA_MAC_VER_18 154 
#define  RTL_GIGA_MAC_VER_19 153 
#define  RTL_GIGA_MAC_VER_20 152 
#define  RTL_GIGA_MAC_VER_21 151 
#define  RTL_GIGA_MAC_VER_22 150 
#define  RTL_GIGA_MAC_VER_23 149 
#define  RTL_GIGA_MAC_VER_24 148 
#define  RTL_GIGA_MAC_VER_25 147 
#define  RTL_GIGA_MAC_VER_26 146 
#define  RTL_GIGA_MAC_VER_27 145 
#define  RTL_GIGA_MAC_VER_28 144 
#define  RTL_GIGA_MAC_VER_31 143 
#define  RTL_GIGA_MAC_VER_32 142 
#define  RTL_GIGA_MAC_VER_33 141 
#define  RTL_GIGA_MAC_VER_34 140 
#define  RTL_GIGA_MAC_VER_35 139 
#define  RTL_GIGA_MAC_VER_36 138 
#define  RTL_GIGA_MAC_VER_38 137 
#define  RTL_GIGA_MAC_VER_40 136 
#define  RTL_GIGA_MAC_VER_41 135 
#define  RTL_GIGA_MAC_VER_42 134 
#define  RTL_GIGA_MAC_VER_44 133 
#define  RTL_GIGA_MAC_VER_45 132 
#define  RTL_GIGA_MAC_VER_46 131 
#define  RTL_GIGA_MAC_VER_49 130 
#define  RTL_GIGA_MAC_VER_50 129 
#define  RTL_GIGA_MAC_VER_51 128 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RxFIFOOver ; 
 int RxOverflow ; 
 int /*<<< orphan*/  TxPacketMax ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtl_hw_start_8168bb (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168bef (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168c_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168c_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168c_3 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168c_4 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168cp_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168cp_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168cp_3 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168d (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168d_4 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168dp (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168e_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168e_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168ep_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168ep_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168ep_3 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168f_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168g_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168g_2 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8168h_1 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8411 (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start_8411_2 (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8168(struct rtl8169_private *tp)
{
	RTL_W8(tp, MaxTxPacketSize, TxPacketMax);

	tp->cp_cmd &= ~INTT_MASK;
	tp->cp_cmd |= PktCntrDisable | INTT_1;
	RTL_W16(tp, CPlusCmd, tp->cp_cmd);

	RTL_W16(tp, IntrMitigate, 0x5100);

	/* Work around for RxFIFO overflow. */
	if (tp->mac_version == RTL_GIGA_MAC_VER_11) {
		tp->event_slow |= RxFIFOOver | PCSTimeout;
		tp->event_slow &= ~RxOverflow;
	}

	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_11:
		rtl_hw_start_8168bb(tp);
		break;

	case RTL_GIGA_MAC_VER_12:
	case RTL_GIGA_MAC_VER_17:
		rtl_hw_start_8168bef(tp);
		break;

	case RTL_GIGA_MAC_VER_18:
		rtl_hw_start_8168cp_1(tp);
		break;

	case RTL_GIGA_MAC_VER_19:
		rtl_hw_start_8168c_1(tp);
		break;

	case RTL_GIGA_MAC_VER_20:
		rtl_hw_start_8168c_2(tp);
		break;

	case RTL_GIGA_MAC_VER_21:
		rtl_hw_start_8168c_3(tp);
		break;

	case RTL_GIGA_MAC_VER_22:
		rtl_hw_start_8168c_4(tp);
		break;

	case RTL_GIGA_MAC_VER_23:
		rtl_hw_start_8168cp_2(tp);
		break;

	case RTL_GIGA_MAC_VER_24:
		rtl_hw_start_8168cp_3(tp);
		break;

	case RTL_GIGA_MAC_VER_25:
	case RTL_GIGA_MAC_VER_26:
	case RTL_GIGA_MAC_VER_27:
		rtl_hw_start_8168d(tp);
		break;

	case RTL_GIGA_MAC_VER_28:
		rtl_hw_start_8168d_4(tp);
		break;

	case RTL_GIGA_MAC_VER_31:
		rtl_hw_start_8168dp(tp);
		break;

	case RTL_GIGA_MAC_VER_32:
	case RTL_GIGA_MAC_VER_33:
		rtl_hw_start_8168e_1(tp);
		break;
	case RTL_GIGA_MAC_VER_34:
		rtl_hw_start_8168e_2(tp);
		break;

	case RTL_GIGA_MAC_VER_35:
	case RTL_GIGA_MAC_VER_36:
		rtl_hw_start_8168f_1(tp);
		break;

	case RTL_GIGA_MAC_VER_38:
		rtl_hw_start_8411(tp);
		break;

	case RTL_GIGA_MAC_VER_40:
	case RTL_GIGA_MAC_VER_41:
		rtl_hw_start_8168g_1(tp);
		break;
	case RTL_GIGA_MAC_VER_42:
		rtl_hw_start_8168g_2(tp);
		break;

	case RTL_GIGA_MAC_VER_44:
		rtl_hw_start_8411_2(tp);
		break;

	case RTL_GIGA_MAC_VER_45:
	case RTL_GIGA_MAC_VER_46:
		rtl_hw_start_8168h_1(tp);
		break;

	case RTL_GIGA_MAC_VER_49:
		rtl_hw_start_8168ep_1(tp);
		break;

	case RTL_GIGA_MAC_VER_50:
		rtl_hw_start_8168ep_2(tp);
		break;

	case RTL_GIGA_MAC_VER_51:
		rtl_hw_start_8168ep_3(tp);
		break;

	default:
		netif_err(tp, drv, tp->dev,
			  "unknown chipset (mac_version = %d)\n",
			  tp->mac_version);
		break;
	}
}