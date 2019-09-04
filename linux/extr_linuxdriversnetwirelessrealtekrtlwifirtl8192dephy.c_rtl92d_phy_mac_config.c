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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ macphymode; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int MAC_2T_ARRAYLENGTH ; 
 int REG_MAX_AGGR_NUM ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SINGLEMAC_SINGLEPHY ; 
 int* rtl8192de_mac_2tarray ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 

bool rtl92d_phy_mac_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;
	u32 arraylength;
	u32 *ptrarray;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "Read Rtl819XMACPHY_Array\n");
	arraylength = MAC_2T_ARRAYLENGTH;
	ptrarray = rtl8192de_mac_2tarray;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "Img:Rtl819XMAC_Array\n");
	for (i = 0; i < arraylength; i = i + 2)
		rtl_write_byte(rtlpriv, ptrarray[i], (u8) ptrarray[i + 1]);
	if (rtlpriv->rtlhal.macphymode == SINGLEMAC_SINGLEPHY) {
		/* improve 2-stream TX EVM */
		/* rtl_write_byte(rtlpriv, 0x14,0x71); */
		/* AMPDU aggregation number 9 */
		/* rtl_write_word(rtlpriv, REG_MAX_AGGR_NUM, MAX_AGGR_NUM); */
		rtl_write_byte(rtlpriv, REG_MAX_AGGR_NUM, 0x0B);
	} else {
		/* 92D need to test to decide the num. */
		rtl_write_byte(rtlpriv, REG_MAX_AGGR_NUM, 0x07);
	}
	return true;
}