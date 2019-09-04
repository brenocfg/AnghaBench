#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_8__ {int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_7__ {int rfkill_state; } ;
struct rtl_priv {TYPE_4__ locks; TYPE_3__ rfkill; TYPE_2__* cfg; int /*<<< orphan*/  status; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* radio_onoff_checking ) (struct ieee80211_hw*,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RTL_STATUS_INTERFACE_START ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int stub1 (struct ieee80211_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl_op_rfkill_poll(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	bool radio_state;
	bool blocked;
	u8 valid = 0;

	if (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		return;

	mutex_lock(&rtlpriv->locks.conf_mutex);

	/*if Radio On return true here */
	radio_state = rtlpriv->cfg->ops->radio_onoff_checking(hw, &valid);

	if (valid) {
		if (unlikely(radio_state != rtlpriv->rfkill.rfkill_state)) {
			rtlpriv->rfkill.rfkill_state = radio_state;

			RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
				 "wireless radio switch turned %s\n",
				  radio_state ? "on" : "off");

			blocked = (rtlpriv->rfkill.rfkill_state == 1) ? 0 : 1;
			wiphy_rfkill_set_hw_state(hw->wiphy, blocked);
		}
	}

	mutex_unlock(&rtlpriv->locks.conf_mutex);
}