#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int rfkill_state; } ;
struct rtl_priv {TYPE_3__ rfkill; TYPE_2__* cfg; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* radio_onoff_checking ) (struct ieee80211_hw*,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int stub1 (struct ieee80211_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiphy_rfkill_start_polling (int /*<<< orphan*/ ) ; 

void rtl_init_rfkill(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	bool radio_state;
	bool blocked;
	u8 valid = 0;

	/*set init state to on */
	rtlpriv->rfkill.rfkill_state = true;
	wiphy_rfkill_set_hw_state(hw->wiphy, 0);

	radio_state = rtlpriv->cfg->ops->radio_onoff_checking(hw, &valid);

	if (valid) {
		pr_info("rtlwifi: wireless switch is %s\n",
			rtlpriv->rfkill.rfkill_state ? "on" : "off");

		rtlpriv->rfkill.rfkill_state = radio_state;

		blocked = (rtlpriv->rfkill.rfkill_state == 1) ? 0 : 1;
		wiphy_rfkill_set_hw_state(hw->wiphy, blocked);
	}

	wiphy_rfkill_start_polling(hw->wiphy);
}