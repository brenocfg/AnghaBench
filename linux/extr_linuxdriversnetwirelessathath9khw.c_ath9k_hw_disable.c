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

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_PM_AWAKE ; 
 int /*<<< orphan*/  ATH9K_RESET_COLD ; 
 int /*<<< orphan*/  ath9k_hw_init_pll (struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_hw_set_reset_reg (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setpower (struct ath_hw*,int /*<<< orphan*/ ) ; 

bool ath9k_hw_disable(struct ath_hw *ah)
{
	if (!ath9k_hw_setpower(ah, ATH9K_PM_AWAKE))
		return false;

	if (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_COLD))
		return false;

	ath9k_hw_init_pll(ah, NULL);
	return true;
}