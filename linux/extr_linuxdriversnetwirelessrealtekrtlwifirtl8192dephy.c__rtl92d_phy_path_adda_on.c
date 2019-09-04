#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_2__ {scalar_t__ interfaceindex; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 size_t IQK_ADDA_REG_NUM ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,size_t,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void _rtl92d_phy_path_adda_on(struct ieee80211_hw *hw,
		u32 *adda_reg, bool patha_on, bool is2t)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 pathon;
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "ADDA ON.\n");
	pathon = patha_on ? 0x04db25a4 : 0x0b1b25a4;
	if (patha_on)
		pathon = rtlpriv->rtlhal.interfaceindex == 0 ?
		    0x04db25a4 : 0x0b1b25a4;
	for (i = 0; i < IQK_ADDA_REG_NUM; i++)
		rtl_set_bbreg(hw, adda_reg[i], MASKDWORD, pathon);
}