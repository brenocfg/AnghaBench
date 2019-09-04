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
struct rtl8169_private {int dummy; } ;
struct ephy_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ephy_info const*) ; 
 int /*<<< orphan*/  DLLPR ; 
 int /*<<< orphan*/  MISC_1 ; 
 int PFM_D3COLD_EN ; 
 int PFM_EN ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int r8168_mac_ocp_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_hw_aspm_clkreq_enable (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_hw_start_8168ep (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8168ep_3(struct rtl8169_private *tp)
{
	u32 data;
	static const struct ephy_info e_info_8168ep_3[] = {
		{ 0x00, 0xffff,	0x10a3 },
		{ 0x19, 0xffff,	0x7c00 },
		{ 0x1e, 0xffff,	0x20eb },
		{ 0x0d, 0xffff,	0x1666 }
	};

	/* disable aspm and clock request before access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168ep_3, ARRAY_SIZE(e_info_8168ep_3));

	rtl_hw_start_8168ep(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);
	RTL_W8(tp, MISC_1, RTL_R8(tp, MISC_1) & ~PFM_D3COLD_EN);

	data = r8168_mac_ocp_read(tp, 0xd3e2);
	data &= 0xf000;
	data |= 0x0271;
	r8168_mac_ocp_write(tp, 0xd3e2, data);

	data = r8168_mac_ocp_read(tp, 0xd3e4);
	data &= 0xff00;
	r8168_mac_ocp_write(tp, 0xd3e4, data);

	data = r8168_mac_ocp_read(tp, 0xe860);
	data |= 0x0080;
	r8168_mac_ocp_write(tp, 0xe860, data);

	rtl_hw_aspm_clkreq_enable(tp, true);
}