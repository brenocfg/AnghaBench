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
struct ephy_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ephy_info const*) ; 
 int ASPM_en ; 
 int ClkReqEn ; 
 int /*<<< orphan*/  Config2 ; 
 int /*<<< orphan*/  Config5 ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_hw_start_8168g (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8168g_2(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168g_2[] = {
		{ 0x00, 0x0000,	0x0008 },
		{ 0x0c, 0x3df0,	0x0200 },
		{ 0x19, 0xffff,	0xfc00 },
		{ 0x1e, 0xffff,	0x20eb }
	};

	rtl_hw_start_8168g(tp);

	/* disable aspm and clock request before access ephy */
	RTL_W8(tp, Config2, RTL_R8(tp, Config2) & ~ClkReqEn);
	RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~ASPM_en);
	rtl_ephy_init(tp, e_info_8168g_2, ARRAY_SIZE(e_info_8168g_2));
}