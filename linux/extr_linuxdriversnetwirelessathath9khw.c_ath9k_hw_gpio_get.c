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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ num_gpio_pins; int gpio_mask; int gpio_requested; } ;
struct ath_hw {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7010_GPIO_IN ; 
 int /*<<< orphan*/  AR9271_GPIO_IN_VAL ; 
 int /*<<< orphan*/  AR9285_GPIO_IN_VAL ; 
 int /*<<< orphan*/  AR9287_GPIO_IN_VAL ; 
 int /*<<< orphan*/  AR928X_GPIO_IN_VAL ; 
 scalar_t__ AR_DEVID_7010 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_GPIO_IN ; 
 int /*<<< orphan*/  AR_GPIO_IN_OUT ; 
 int /*<<< orphan*/  AR_GPIO_IN_VAL ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int BIT (scalar_t__) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int gpio_get_value (scalar_t__) ; 

u32 ath9k_hw_gpio_get(struct ath_hw *ah, u32 gpio)
{
	u32 val = 0xffffffff;

#define MS_REG_READ(x, y) \
	(MS(REG_READ(ah, AR_GPIO_IN_OUT), x##_GPIO_IN_VAL) & BIT(y))

	WARN_ON(gpio >= ah->caps.num_gpio_pins);

	if (BIT(gpio) & ah->caps.gpio_mask) {
		if (AR_SREV_9271(ah))
			val = MS_REG_READ(AR9271, gpio);
		else if (AR_SREV_9287(ah))
			val = MS_REG_READ(AR9287, gpio);
		else if (AR_SREV_9285(ah))
			val = MS_REG_READ(AR9285, gpio);
		else if (AR_SREV_9280(ah))
			val = MS_REG_READ(AR928X, gpio);
		else if (AR_DEVID_7010(ah))
			val = REG_READ(ah, AR7010_GPIO_IN) & BIT(gpio);
		else if (AR_SREV_9300_20_OR_LATER(ah))
			val = REG_READ(ah, AR_GPIO_IN) & BIT(gpio);
		else
			val = MS_REG_READ(AR, gpio);
	} else if (BIT(gpio) & ah->caps.gpio_requested) {
		val = gpio_get_value(gpio) & BIT(gpio);
	} else {
		WARN_ON(1);
	}

	return !!val;
}