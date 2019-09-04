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
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AFE_PLL_CTRL ; 
 int /*<<< orphan*/  REG_AFE_XTAL_CTRL ; 
 int /*<<< orphan*/  RF_A ; 
 int /*<<< orphan*/  rtl8723au_radioa_1t_init_table ; 
 int rtl8xxxu_init_phy_rf (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl8723au_init_phy_rf(struct rtl8xxxu_priv *priv)
{
	int ret;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8723au_radioa_1t_init_table, RF_A);

	/* Reduce 80M spur */
	rtl8xxxu_write32(priv, REG_AFE_XTAL_CTRL, 0x0381808d);
	rtl8xxxu_write32(priv, REG_AFE_PLL_CTRL, 0xf0ffff83);
	rtl8xxxu_write32(priv, REG_AFE_PLL_CTRL, 0xf0ffff82);
	rtl8xxxu_write32(priv, REG_AFE_PLL_CTRL, 0xf0ffff83);

	return ret;
}