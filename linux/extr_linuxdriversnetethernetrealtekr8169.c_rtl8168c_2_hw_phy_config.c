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
struct phy_reg {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct phy_reg const*) ; 
 int /*<<< orphan*/  rtl_patchphy (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_writephy_batch (struct rtl8169_private*,struct phy_reg const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8168c_2_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x12, 0x2300 },
		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf099 },
		{ 0x04, 0x9800 },
		{ 0x04, 0x9000 },
		{ 0x1d, 0x3d98 },
		{ 0x1f, 0x0002 },
		{ 0x0c, 0x7eb8 },
		{ 0x06, 0x0761 },
		{ 0x1f, 0x0003 },
		{ 0x16, 0x0f0a },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy_batch(tp, phy_reg_init, ARRAY_SIZE(phy_reg_init));

	rtl_patchphy(tp, 0x16, 1 << 0);
	rtl_patchphy(tp, 0x14, 1 << 5);
	rtl_patchphy(tp, 0x0d, 1 << 5);
	rtl_writephy(tp, 0x1f, 0x0000);
}