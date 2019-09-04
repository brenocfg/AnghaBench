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
typedef  int u32 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AFE_CTRL4 ; 
 int /*<<< orphan*/  REG_AFE_PLL_CTRL ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192e_crystal_afe_adjust(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u32 val32;

	/*
	 * 40Mhz crystal source, MAC 0x28[2]=0
	 */
	val8 = rtl8xxxu_read8(priv, REG_AFE_PLL_CTRL);
	val8 &= 0xfb;
	rtl8xxxu_write8(priv, REG_AFE_PLL_CTRL, val8);

	val32 = rtl8xxxu_read32(priv, REG_AFE_CTRL4);
	val32 &= 0xfffffc7f;
	rtl8xxxu_write32(priv, REG_AFE_CTRL4, val32);

	/*
	 * 92e AFE parameter
	 * AFE PLL KVCO selection, MAC 0x28[6]=1
	 */
	val8 = rtl8xxxu_read8(priv, REG_AFE_PLL_CTRL);
	val8 &= 0xbf;
	rtl8xxxu_write8(priv, REG_AFE_PLL_CTRL, val8);

	/*
	 * AFE PLL KVCO selection, MAC 0x78[21]=0
	 */
	val32 = rtl8xxxu_read32(priv, REG_AFE_CTRL4);
	val32 &= 0xffdfffff;
	rtl8xxxu_write32(priv, REG_AFE_CTRL4, val32);
}