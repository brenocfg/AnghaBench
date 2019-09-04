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
typedef  int u8 ;
typedef  int u16 ;
struct rtl8xxxu_priv {scalar_t__ hi_pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RF_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC ; 
 int RF_ENABLE ; 
 int RF_RSTB ; 
 int RF_SDMRSTB ; 
 int SYS_FUNC_BBRSTB ; 
 int SYS_FUNC_BB_GLB_RSTN ; 
 int SYS_FUNC_DIO_RF ; 
 int SYS_FUNC_USBA ; 
 int SYS_FUNC_USBD ; 
 int /*<<< orphan*/  rtl8192eu_phy_init_table ; 
 int /*<<< orphan*/  rtl8xxx_agc_8192eu_highpa_table ; 
 int /*<<< orphan*/  rtl8xxx_agc_8192eu_std_table ; 
 int /*<<< orphan*/  rtl8xxxu_init_phy_regs (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192eu_init_phy_bb(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;

	val16 = rtl8xxxu_read16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_BB_GLB_RSTN | SYS_FUNC_BBRSTB | SYS_FUNC_DIO_RF;
	rtl8xxxu_write16(priv, REG_SYS_FUNC, val16);

	/* 6. 0x1f[7:0] = 0x07 */
	val8 = RF_ENABLE | RF_RSTB | RF_SDMRSTB;
	rtl8xxxu_write8(priv, REG_RF_CTRL, val8);

	val16 = rtl8xxxu_read16(priv, REG_SYS_FUNC);
	val16 |= (SYS_FUNC_USBA | SYS_FUNC_USBD | SYS_FUNC_DIO_RF |
		  SYS_FUNC_BB_GLB_RSTN | SYS_FUNC_BBRSTB);
	rtl8xxxu_write16(priv, REG_SYS_FUNC, val16);
	val8 = RF_ENABLE | RF_RSTB | RF_SDMRSTB;
	rtl8xxxu_write8(priv, REG_RF_CTRL, val8);
	rtl8xxxu_init_phy_regs(priv, rtl8192eu_phy_init_table);

	if (priv->hi_pa)
		rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_8192eu_highpa_table);
	else
		rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_8192eu_std_table);
}