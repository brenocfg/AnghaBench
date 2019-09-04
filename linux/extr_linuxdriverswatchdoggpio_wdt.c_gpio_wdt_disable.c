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
struct gpio_wdt_priv {scalar_t__ hw_algo; int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
 scalar_t__ HW_ALGO_TOGGLE ; 
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gpio_wdt_disable(struct gpio_wdt_priv *priv)
{
	/* Eternal ping */
	gpiod_set_value_cansleep(priv->gpiod, 1);

	/* Put GPIO back to tristate */
	if (priv->hw_algo == HW_ALGO_TOGGLE)
		gpiod_direction_input(priv->gpiod);
}