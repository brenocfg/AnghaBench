#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int /*<<< orphan*/  (* brightness_set ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct rt2x00_led {int /*<<< orphan*/  flags; TYPE_1__ led_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  LED_REGISTERED ; 
 int LED_SUSPENDED ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2x00leds_unregister_led(struct rt2x00_led *led)
{
	led_classdev_unregister(&led->led_dev);

	/*
	 * This might look weird, but when we are unregistering while
	 * suspended the led is already off, and since we haven't
	 * fully resumed yet, access to the device might not be
	 * possible yet.
	 */
	if (!(led->led_dev.flags & LED_SUSPENDED))
		led->led_dev.brightness_set(&led->led_dev, LED_OFF);

	led->flags &= ~LED_REGISTERED;
}