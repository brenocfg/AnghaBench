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
struct watchdog_device {int dummy; } ;
struct gpio_wdt_priv {int hw_algo; int state; int /*<<< orphan*/  gpiod; } ;

/* Variables and functions */
#define  HW_ALGO_LEVEL 129 
#define  HW_ALGO_TOGGLE 128 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 struct gpio_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int gpio_wdt_ping(struct watchdog_device *wdd)
{
	struct gpio_wdt_priv *priv = watchdog_get_drvdata(wdd);

	switch (priv->hw_algo) {
	case HW_ALGO_TOGGLE:
		/* Toggle output pin */
		priv->state = !priv->state;
		gpiod_set_value_cansleep(priv->gpiod, priv->state);
		break;
	case HW_ALGO_LEVEL:
		/* Pulse */
		gpiod_set_value_cansleep(priv->gpiod, 1);
		udelay(1);
		gpiod_set_value_cansleep(priv->gpiod, 0);
		break;
	}
	return 0;
}