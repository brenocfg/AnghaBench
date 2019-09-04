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
struct ath_hw {int dummy; } ;
typedef  enum ath_stomp_type { ____Placeholder_ath_stomp_type } ath_stomp_type ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BT_COEX_WGHT ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_STOMP_ALL_WLAN_WGHT ; 
 int /*<<< orphan*/  AR_STOMP_LOW_WLAN_WGHT ; 
 int /*<<< orphan*/  AR_STOMP_NONE_WLAN_WGHT ; 
#define  ATH_BTCOEX_STOMP_ALL 130 
#define  ATH_BTCOEX_STOMP_LOW 129 
#define  ATH_BTCOEX_STOMP_NONE 128 
 int /*<<< orphan*/  BTCOEX ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_set_weight (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void ath9k_hw_btcoex_bt_stomp(struct ath_hw *ah,
			      enum ath_stomp_type stomp_type)
{
	if (AR_SREV_9300_20_OR_LATER(ah)) {
		ath9k_hw_btcoex_set_weight(ah, 0, 0, stomp_type);
		return;
	}

	switch (stomp_type) {
	case ATH_BTCOEX_STOMP_ALL:
		ath9k_hw_btcoex_set_weight(ah, AR_BT_COEX_WGHT,
					   AR_STOMP_ALL_WLAN_WGHT, 0);
		break;
	case ATH_BTCOEX_STOMP_LOW:
		ath9k_hw_btcoex_set_weight(ah, AR_BT_COEX_WGHT,
					   AR_STOMP_LOW_WLAN_WGHT, 0);
		break;
	case ATH_BTCOEX_STOMP_NONE:
		ath9k_hw_btcoex_set_weight(ah, AR_BT_COEX_WGHT,
					   AR_STOMP_NONE_WLAN_WGHT, 0);
		break;
	default:
		ath_dbg(ath9k_hw_common(ah), BTCOEX, "Invalid Stomptype\n");
		break;
	}
}