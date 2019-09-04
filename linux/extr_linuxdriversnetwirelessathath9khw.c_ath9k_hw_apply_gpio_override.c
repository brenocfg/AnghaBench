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
typedef  int u32 ;
struct ath_hw {int gpio_mask; int gpio_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIO_OUTPUT_MUX_AS_OUTPUT ; 
 int BIT (int) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_free (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_request_out (struct ath_hw*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_set_gpio (struct ath_hw*,int,int) ; 

__attribute__((used)) static void ath9k_hw_apply_gpio_override(struct ath_hw *ah)
{
	u32 gpio_mask = ah->gpio_mask;
	int i;

	for (i = 0; gpio_mask; i++, gpio_mask >>= 1) {
		if (!(gpio_mask & 1))
			continue;

		ath9k_hw_gpio_request_out(ah, i, NULL,
					  AR_GPIO_OUTPUT_MUX_AS_OUTPUT);
		ath9k_hw_set_gpio(ah, i, !!(ah->gpio_val & BIT(i)));
		ath9k_hw_gpio_free(ah, i);
	}
}