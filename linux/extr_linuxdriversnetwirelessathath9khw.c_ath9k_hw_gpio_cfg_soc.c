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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int gpio_requested; } ;
struct ath_hw {TYPE_1__ caps; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void ath9k_hw_gpio_cfg_soc(struct ath_hw *ah, u32 gpio, bool out,
				  const char *label)
{
	if (ah->caps.gpio_requested & BIT(gpio))
		return;

	/* may be requested by BSP, free anyway */
	gpio_free(gpio);

	if (gpio_request_one(gpio, out ? GPIOF_OUT_INIT_LOW : GPIOF_IN, label))
		return;

	ah->caps.gpio_requested |= BIT(gpio);
}