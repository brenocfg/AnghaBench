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
struct TYPE_2__ {char const* default_trigger; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  name; } ;
struct led_nu801_led_data {int level; TYPE_1__ cdev; struct led_nu801_data* controller; int /*<<< orphan*/  name; } ;
struct led_nu801_data {int num_leds; int /*<<< orphan*/  name; int /*<<< orphan*/  device_name; struct led_nu801_led_data* led_chain; } ;
struct device {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int NUM_COLORS ; 
 int /*<<< orphan*/  kfree (struct led_nu801_led_data*) ; 
 int led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_nu801_set ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int led_nu801_create(struct led_nu801_data *controller,
				    struct device *parent,
				    int index,
				    enum led_brightness brightness,
#ifdef CONFIG_LEDS_TRIGGERS
				    const char *default_trigger,
#endif
				    const char *color)
{
	struct led_nu801_led_data *led = &controller->led_chain[index];
	int ret;

	scnprintf(led->name, sizeof(led->name), "%s:%s:%s%d",
		  controller->device_name, color, controller->name,
		  (controller->num_leds - (index + 1)) / NUM_COLORS);
	led->cdev.name = led->name;
	led->cdev.brightness_set = led_nu801_set;
#ifdef CONFIG_LEDS_TRIGGERS
	led->cdev.default_trigger = default_trigger;
#endif
	led->level = brightness;
	led->controller = controller;
	ret = led_classdev_register(parent, &led->cdev);
	if (ret < 0)
		goto err;

	return 0;

err:
	kfree(led);
	return ret;
}