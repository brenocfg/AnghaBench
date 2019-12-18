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
struct TYPE_4__ {TYPE_1__* usbdev; } ;
struct usb_line6_toneport {struct toneport_led* leds; TYPE_2__ line6; } ;
struct led_classdev {int max_brightness; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  brightness; int /*<<< orphan*/  name; } ;
struct toneport_led {int registered; int /*<<< orphan*/  name; struct usb_line6_toneport* toneport; struct led_classdev dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 char* dev_name (struct device*) ; 
 int led_classdev_register (struct device*,struct led_classdev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  toneport_led_brightness_set ; 
 char** toneport_led_colors ; 
 int /*<<< orphan*/ * toneport_led_init_vals ; 

__attribute__((used)) static int toneport_init_leds(struct usb_line6_toneport *toneport)
{
	struct device *dev = &toneport->line6.usbdev->dev;
	int i, err;

	for (i = 0; i < 2; i++) {
		struct toneport_led *led = &toneport->leds[i];
		struct led_classdev *leddev = &led->dev;

		led->toneport = toneport;
		snprintf(led->name, sizeof(led->name), "%s::%s",
			 dev_name(dev), toneport_led_colors[i]);
		leddev->name = led->name;
		leddev->brightness = toneport_led_init_vals[i];
		leddev->max_brightness = 0x26;
		leddev->brightness_set = toneport_led_brightness_set;
		err = led_classdev_register(dev, leddev);
		if (err)
			return err;
		led->registered = true;
	}

	return 0;
}