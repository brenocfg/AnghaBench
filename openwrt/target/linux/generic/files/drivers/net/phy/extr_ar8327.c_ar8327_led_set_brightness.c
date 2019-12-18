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
typedef  int /*<<< orphan*/  u8 ;
struct led_classdev {int dummy; } ;
struct ar8327_led {int active_low; int enable_hw_mode; int /*<<< orphan*/  lock; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327_LED_PATTERN_OFF ; 
 int /*<<< orphan*/  AR8327_LED_PATTERN_ON ; 
 int LED_OFF ; 
 int /*<<< orphan*/  ar8327_led_schedule_change (struct ar8327_led*,int /*<<< orphan*/ ) ; 
 struct ar8327_led* led_cdev_to_ar8327_led (struct led_classdev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ar8327_led_set_brightness(struct led_classdev *led_cdev,
			  enum led_brightness brightness)
{
	struct ar8327_led *aled = led_cdev_to_ar8327_led(led_cdev);
	u8 pattern;
	bool active;

	active = (brightness != LED_OFF);
	active ^= aled->active_low;

	pattern = (active) ? AR8327_LED_PATTERN_ON :
			     AR8327_LED_PATTERN_OFF;

	spin_lock(&aled->lock);

	aled->enable_hw_mode = false;
	ar8327_led_schedule_change(aled, pattern);

	spin_unlock(&aled->lock);
}