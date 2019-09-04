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
struct ath_hw {int paprd_target_power; struct ath9k_channel* curchan; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_POWERTX_RATE5 ; 
 int /*<<< orphan*/  AR_PHY_POWERTX_RATE5_POWERTXHT20_0 ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 unsigned int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int abs (int) ; 
 unsigned int ar9003_get_paprd_scale_factor (struct ath_hw*,struct ath9k_channel*) ; 

__attribute__((used)) static int ar9003_get_training_power_2g(struct ath_hw *ah)
{
	struct ath9k_channel *chan = ah->curchan;
	unsigned int power, scale, delta;

	scale = ar9003_get_paprd_scale_factor(ah, chan);

	if (AR_SREV_9330(ah) || AR_SREV_9340(ah) ||
	    AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		power = ah->paprd_target_power + 2;
	} else if (AR_SREV_9485(ah)) {
		power = 25;
	} else {
		power = REG_READ_FIELD(ah, AR_PHY_POWERTX_RATE5,
				       AR_PHY_POWERTX_RATE5_POWERTXHT20_0);

		delta = abs((int) ah->paprd_target_power - (int) power);
		if (delta > scale)
			return -1;

		if (delta < 4)
			power -= 4 - delta;
	}

	return power;
}