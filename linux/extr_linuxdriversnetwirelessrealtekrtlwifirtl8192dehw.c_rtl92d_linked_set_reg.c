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
typedef  size_t u8 ;
struct rtl_phy {size_t current_channel; TYPE_1__* iqk_matrix; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iqk_done; } ;

/* Variables and functions */
 int COMP_INIT ; 
 int COMP_SCAN ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int,int /*<<< orphan*/ ,char*,size_t) ; 
 size_t rtl92d_get_rightchnlplace_for_iqk (size_t) ; 
 int /*<<< orphan*/  rtl92d_phy_iq_calibrate (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92d_linked_set_reg(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 indexforchannel;
	u8 channel = rtlphy->current_channel;

	indexforchannel = rtl92d_get_rightchnlplace_for_iqk(channel);
	if (!rtlphy->iqk_matrix[indexforchannel].iqk_done) {
		RT_TRACE(rtlpriv, COMP_SCAN | COMP_INIT, DBG_DMESG,
			 "Do IQK for channel:%d\n", channel);
		rtl92d_phy_iq_calibrate(hw);
	}
}