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
typedef  int u16 ;
struct rtl8169_private {int dummy; } ;
struct ephy_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ephy_info const*) ; 
 int /*<<< orphan*/  DLLPR ; 
 int /*<<< orphan*/  EEE_LED ; 
 int /*<<< orphan*/  ERIAR_EXGMAC ; 
 int /*<<< orphan*/  ERIAR_MASK_0001 ; 
 int /*<<< orphan*/  ERIAR_MASK_0011 ; 
 int /*<<< orphan*/  ERIAR_MASK_0101 ; 
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 int EarlySize ; 
 int /*<<< orphan*/  MISC ; 
 int /*<<< orphan*/  MISC_1 ; 
 int /*<<< orphan*/  MaxTxPacketSize ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_READRQ_4096B ; 
 int PFM_D3COLD_EN ; 
 int PFM_EN ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int RXDV_GATED_EN ; 
 int TX_10M_PS_EN ; 
 int r8168_mac_ocp_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_hw_aspm_clkreq_enable (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_pcie_state_l2l3_enable (struct rtl8169_private*,int) ; 
 int rtl_readphy (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_tx_performance_tweak (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_w0w1_eri (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl_hw_start_8168h_1(struct rtl8169_private *tp)
{
	int rg_saw_cnt;
	u32 data;
	static const struct ephy_info e_info_8168h_1[] = {
		{ 0x1e, 0x0800,	0x0001 },
		{ 0x1d, 0x0000,	0x0800 },
		{ 0x05, 0xffff,	0x2089 },
		{ 0x06, 0xffff,	0x5881 },
		{ 0x04, 0xffff,	0x154a },
		{ 0x01, 0xffff,	0x068b }
	};

	/* disable aspm and clock request before access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168h_1, ARRAY_SIZE(e_info_8168h_1));

	rtl_eri_write(tp, 0xc8, ERIAR_MASK_0101, 0x00080002, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xcc, ERIAR_MASK_0001, 0x38, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xd0, ERIAR_MASK_0001, 0x48, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xe8, ERIAR_MASK_1111, 0x00100006, ERIAR_EXGMAC);

	rtl_set_def_aspm_entry_latency(tp);

	rtl_tx_performance_tweak(tp, PCI_EXP_DEVCTL_READRQ_4096B);

	rtl_w0w1_eri(tp, 0xdc, ERIAR_MASK_0001, 0x00, 0x01, ERIAR_EXGMAC);
	rtl_w0w1_eri(tp, 0xdc, ERIAR_MASK_0001, 0x01, 0x00, ERIAR_EXGMAC);

	rtl_w0w1_eri(tp, 0xdc, ERIAR_MASK_1111, 0x0010, 0x00, ERIAR_EXGMAC);

	rtl_w0w1_eri(tp, 0xd4, ERIAR_MASK_1111, 0x1f00, 0x00, ERIAR_EXGMAC);

	rtl_eri_write(tp, 0x5f0, ERIAR_MASK_0011, 0x4f87, ERIAR_EXGMAC);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);
	RTL_W8(tp, MaxTxPacketSize, EarlySize);

	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000, ERIAR_EXGMAC);

	/* Adjust EEE LED frequency */
	RTL_W8(tp, EEE_LED, RTL_R8(tp, EEE_LED) & ~0x07);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);
	RTL_W8(tp, MISC_1, RTL_R8(tp, MISC_1) & ~PFM_D3COLD_EN);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~TX_10M_PS_EN);

	rtl_w0w1_eri(tp, 0x1b0, ERIAR_MASK_0011, 0x0000, 0x1000, ERIAR_EXGMAC);

	rtl_pcie_state_l2l3_enable(tp, false);

	rtl_writephy(tp, 0x1f, 0x0c42);
	rg_saw_cnt = (rtl_readphy(tp, 0x13) & 0x3fff);
	rtl_writephy(tp, 0x1f, 0x0000);
	if (rg_saw_cnt > 0) {
		u16 sw_cnt_1ms_ini;

		sw_cnt_1ms_ini = 16000000/rg_saw_cnt;
		sw_cnt_1ms_ini &= 0x0fff;
		data = r8168_mac_ocp_read(tp, 0xd412);
		data &= ~0x0fff;
		data |= sw_cnt_1ms_ini;
		r8168_mac_ocp_write(tp, 0xd412, data);
	}

	data = r8168_mac_ocp_read(tp, 0xe056);
	data &= ~0xf0;
	data |= 0x70;
	r8168_mac_ocp_write(tp, 0xe056, data);

	data = r8168_mac_ocp_read(tp, 0xe052);
	data &= ~0x6000;
	data |= 0x8008;
	r8168_mac_ocp_write(tp, 0xe052, data);

	data = r8168_mac_ocp_read(tp, 0xe0d6);
	data &= ~0x01ff;
	data |= 0x017f;
	r8168_mac_ocp_write(tp, 0xe0d6, data);

	data = r8168_mac_ocp_read(tp, 0xd420);
	data &= ~0x0fff;
	data |= 0x047f;
	r8168_mac_ocp_write(tp, 0xd420, data);

	r8168_mac_ocp_write(tp, 0xe63e, 0x0001);
	r8168_mac_ocp_write(tp, 0xe63e, 0x0000);
	r8168_mac_ocp_write(tp, 0xc094, 0x0000);
	r8168_mac_ocp_write(tp, 0xc09e, 0x0000);

	rtl_hw_aspm_clkreq_enable(tp, true);
}