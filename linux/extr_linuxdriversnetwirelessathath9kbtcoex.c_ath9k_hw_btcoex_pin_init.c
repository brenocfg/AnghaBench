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
typedef  void* u8 ;
struct ath_btcoex_hw {scalar_t__ scheme; void* btpriority_gpio; void* wlanactive_gpio; void* btactive_gpio; } ;
struct ath_hw {TYPE_1__* dev; struct ath_btcoex_hw btcoex_hw; } ;
struct ath9k_platform_data {void* bt_priority_pin; void* wlan_active_pin; void* bt_active_pin; } ;
struct TYPE_2__ {struct ath9k_platform_data* platform_data; } ;

/* Variables and functions */
 scalar_t__ ATH_BTCOEX_CFG_2WIRE ; 
 scalar_t__ ATH_BTCOEX_CFG_3WIRE ; 

__attribute__((used)) static void ath9k_hw_btcoex_pin_init(struct ath_hw *ah, u8 wlanactive_gpio,
				     u8 btactive_gpio, u8 btpriority_gpio)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	struct ath9k_platform_data *pdata = ah->dev->platform_data;

	if (btcoex_hw->scheme != ATH_BTCOEX_CFG_2WIRE &&
	    btcoex_hw->scheme != ATH_BTCOEX_CFG_3WIRE)
		return;

	/* bt priority GPIO will be ignored by 2 wire scheme */
	if (pdata && (pdata->bt_active_pin || pdata->bt_priority_pin ||
		      pdata->wlan_active_pin)) {
		btcoex_hw->btactive_gpio = pdata->bt_active_pin;
		btcoex_hw->wlanactive_gpio = pdata->wlan_active_pin;
		btcoex_hw->btpriority_gpio = pdata->bt_priority_pin;
	} else {
		btcoex_hw->btactive_gpio = btactive_gpio;
		btcoex_hw->wlanactive_gpio = wlanactive_gpio;
		btcoex_hw->btpriority_gpio = btpriority_gpio;
	}
}