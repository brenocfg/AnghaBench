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
struct ath_btcoex_hw {int /*<<< orphan*/  wlanactive_gpio; int /*<<< orphan*/  btpriority_gpio; int /*<<< orphan*/  btactive_gpio; } ;
struct ath_hw {struct ath_btcoex_hw btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_gpio_free (struct ath_hw*,int /*<<< orphan*/ ) ; 

void ath9k_hw_btcoex_deinit(struct ath_hw *ah)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	ath9k_hw_gpio_free(ah, btcoex_hw->btactive_gpio);
	ath9k_hw_gpio_free(ah, btcoex_hw->btpriority_gpio);
	ath9k_hw_gpio_free(ah, btcoex_hw->wlanactive_gpio);
}