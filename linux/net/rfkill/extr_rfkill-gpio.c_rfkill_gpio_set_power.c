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
struct rfkill_gpio_data {int clk_enabled; int /*<<< orphan*/  clk; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  shutdown_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rfkill_gpio_set_power(void *data, bool blocked)
{
	struct rfkill_gpio_data *rfkill = data;

	if (!blocked && !IS_ERR(rfkill->clk) && !rfkill->clk_enabled)
		clk_enable(rfkill->clk);

	gpiod_set_value_cansleep(rfkill->shutdown_gpio, !blocked);
	gpiod_set_value_cansleep(rfkill->reset_gpio, !blocked);

	if (blocked && !IS_ERR(rfkill->clk) && rfkill->clk_enabled)
		clk_disable(rfkill->clk);

	rfkill->clk_enabled = !blocked;

	return 0;
}