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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int rtl_readphy (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_w0w1_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl8168ep_1_hw_phy_config(struct rtl8169_private *tp)
{
	/* Enable PHY auto speed down */
	rtl_writephy(tp, 0x1f, 0x0a44);
	rtl_w0w1_phy(tp, 0x11, 0x000c, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* patch 10M & ALDPS */
	rtl_writephy(tp, 0x1f, 0x0bcc);
	rtl_w0w1_phy(tp, 0x14, 0x0000, 0x0100);
	rtl_writephy(tp, 0x1f, 0x0a44);
	rtl_w0w1_phy(tp, 0x11, 0x00c0, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8084);
	rtl_w0w1_phy(tp, 0x14, 0x0000, 0x6000);
	rtl_w0w1_phy(tp, 0x10, 0x1003, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Enable EEE auto-fallback function */
	rtl_writephy(tp, 0x1f, 0x0a4b);
	rtl_w0w1_phy(tp, 0x11, 0x0004, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Enable UC LPF tune function */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8012);
	rtl_w0w1_phy(tp, 0x14, 0x8000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* set rg_sel_sdm_rate */
	rtl_writephy(tp, 0x1f, 0x0c42);
	rtl_w0w1_phy(tp, 0x11, 0x4000, 0x2000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Check ALDPS bit, disable it if enabled */
	rtl_writephy(tp, 0x1f, 0x0a43);
	if (rtl_readphy(tp, 0x10) & 0x0004)
		rtl_w0w1_phy(tp, 0x10, 0x0000, 0x0004);

	rtl_writephy(tp, 0x1f, 0x0000);
}