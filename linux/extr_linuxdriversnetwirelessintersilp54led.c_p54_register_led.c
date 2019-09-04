#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* default_trigger; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  name; } ;
struct p54_led_dev {int registered; unsigned int index; TYPE_2__ led_dev; int /*<<< orphan*/  name; TYPE_1__* hw_dev; } ;
struct p54_common {TYPE_1__* hw; struct p54_led_dev* leds; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int EEXIST ; 
 int led_classdev_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  p54_led_brightness_set ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  wiphy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,char*) ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p54_register_led(struct p54_common *priv,
			    unsigned int led_index,
			    char *name, const char *trigger)
{
	struct p54_led_dev *led = &priv->leds[led_index];
	int err;

	if (led->registered)
		return -EEXIST;

	snprintf(led->name, sizeof(led->name), "p54-%s::%s",
		 wiphy_name(priv->hw->wiphy), name);
	led->hw_dev = priv->hw;
	led->index = led_index;
	led->led_dev.name = led->name;
	led->led_dev.default_trigger = trigger;
	led->led_dev.brightness_set = p54_led_brightness_set;

	err = led_classdev_register(wiphy_dev(priv->hw->wiphy), &led->led_dev);
	if (err)
		wiphy_err(priv->hw->wiphy,
			  "Failed to register %s LED.\n", name);
	else
		led->registered = 1;

	return err;
}