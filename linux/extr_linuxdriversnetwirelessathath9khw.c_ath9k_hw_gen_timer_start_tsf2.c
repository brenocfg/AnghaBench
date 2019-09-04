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
struct ath_gen_timer_table {scalar_t__ tsf2_enabled; } ;
struct ath_hw {struct ath_gen_timer_table hw_gen_timers; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DC_AP_STA_EN ; 
 int /*<<< orphan*/  AR_DIRECT_CONNECT ; 
 int /*<<< orphan*/  AR_RESET_TSF ; 
 int /*<<< orphan*/  AR_RESET_TSF2_ONCE ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath9k_hw_gen_timer_start_tsf2(struct ath_hw *ah)
{
	struct ath_gen_timer_table *timer_table = &ah->hw_gen_timers;

	if (timer_table->tsf2_enabled) {
		REG_SET_BIT(ah, AR_DIRECT_CONNECT, AR_DC_AP_STA_EN);
		REG_SET_BIT(ah, AR_RESET_TSF, AR_RESET_TSF2_ONCE);
	}
}