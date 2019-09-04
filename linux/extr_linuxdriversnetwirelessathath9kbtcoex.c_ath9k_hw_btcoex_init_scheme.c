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
struct TYPE_2__ {int hw_caps; } ;
struct ath_btcoex_hw {void* scheme; } ;
struct ath_hw {TYPE_1__ caps; struct ath_btcoex_hw btcoex_hw; } ;
struct ath_common {int /*<<< orphan*/  btcoex_enabled; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int ATH9K_HW_CAP_MCI ; 
 int /*<<< orphan*/  ATH_BTACTIVE_GPIO_9280 ; 
 int /*<<< orphan*/  ATH_BTACTIVE_GPIO_9300 ; 
 void* ATH_BTCOEX_CFG_2WIRE ; 
 void* ATH_BTCOEX_CFG_3WIRE ; 
 void* ATH_BTCOEX_CFG_MCI ; 
 void* ATH_BTCOEX_CFG_NONE ; 
 int /*<<< orphan*/  ATH_BTPRIORITY_GPIO_9285 ; 
 int /*<<< orphan*/  ATH_BTPRIORITY_GPIO_9300 ; 
 int /*<<< orphan*/  ATH_WLANACTIVE_GPIO_9280 ; 
 int /*<<< orphan*/  ATH_WLANACTIVE_GPIO_9300 ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_pin_init (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 

void ath9k_hw_btcoex_init_scheme(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	/*
	 * Check if BTCOEX is globally disabled.
	 */
	if (!common->btcoex_enabled) {
		btcoex_hw->scheme = ATH_BTCOEX_CFG_NONE;
		return;
	}

	if (ah->caps.hw_caps & ATH9K_HW_CAP_MCI) {
		btcoex_hw->scheme = ATH_BTCOEX_CFG_MCI;
	} else if (AR_SREV_9300_20_OR_LATER(ah)) {
		btcoex_hw->scheme = ATH_BTCOEX_CFG_3WIRE;

		ath9k_hw_btcoex_pin_init(ah, ATH_WLANACTIVE_GPIO_9300,
					 ATH_BTACTIVE_GPIO_9300,
					 ATH_BTPRIORITY_GPIO_9300);
	} else if (AR_SREV_9280_20_OR_LATER(ah)) {
		if (AR_SREV_9285(ah))
			btcoex_hw->scheme = ATH_BTCOEX_CFG_3WIRE;
		else
			btcoex_hw->scheme = ATH_BTCOEX_CFG_2WIRE;

		ath9k_hw_btcoex_pin_init(ah, ATH_WLANACTIVE_GPIO_9280,
					 ATH_BTACTIVE_GPIO_9280,
					 ATH_BTPRIORITY_GPIO_9285);
	}
}