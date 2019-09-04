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
struct usb_line6_toneport {struct toneport_led* leds; } ;
struct toneport_led {int registered; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void toneport_remove_leds(struct usb_line6_toneport *toneport)
{
	struct toneport_led *led;
	int i;

	for (i = 0; i < 2; i++) {
		led = &toneport->leds[i];
		if (!led->registered)
			break;
		led_classdev_unregister(&led->dev);
		led->registered = false;
	}
}