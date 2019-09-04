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
struct led_classdev {char* name; int max_brightness; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set; } ;
struct asus_led {int /*<<< orphan*/  work; struct asus_laptop* asus; struct led_classdev led; } ;
struct asus_laptop {scalar_t__ wled_type; scalar_t__ bled_type; TYPE_1__* platform_device; struct asus_led kled; int /*<<< orphan*/  handle; int /*<<< orphan*/  gled; int /*<<< orphan*/  pled; int /*<<< orphan*/  rled; int /*<<< orphan*/  tled; int /*<<< orphan*/  mled; int /*<<< orphan*/  bled; int /*<<< orphan*/  wled; int /*<<< orphan*/  led_workqueue; scalar_t__ is_pega_lucid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  METHOD_BLUETOOTH ; 
 int /*<<< orphan*/  METHOD_GLED ; 
 int /*<<< orphan*/  METHOD_KBD_LIGHT_GET ; 
 int /*<<< orphan*/  METHOD_KBD_LIGHT_SET ; 
 int /*<<< orphan*/  METHOD_MLED ; 
 int /*<<< orphan*/  METHOD_PLED ; 
 int /*<<< orphan*/  METHOD_RLED ; 
 int /*<<< orphan*/  METHOD_TLED ; 
 int /*<<< orphan*/  METHOD_WLAN ; 
 scalar_t__ TYPE_LED ; 
 int /*<<< orphan*/  acpi_check_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_kled_cdev_get ; 
 int /*<<< orphan*/  asus_kled_cdev_set ; 
 int /*<<< orphan*/  asus_kled_cdev_update ; 
 int /*<<< orphan*/  asus_led_exit (struct asus_laptop*) ; 
 int asus_led_register (struct asus_laptop*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int led_classdev_register (int /*<<< orphan*/ *,struct led_classdev*) ; 

__attribute__((used)) static int asus_led_init(struct asus_laptop *asus)
{
	int r = 0;

	/*
	 * The Pegatron Lucid has no physical leds, but all methods are
	 * available in the DSDT...
	 */
	if (asus->is_pega_lucid)
		return 0;

	/*
	 * Functions that actually update the LED's are called from a
	 * workqueue. By doing this as separate work rather than when the LED
	 * subsystem asks, we avoid messing with the Asus ACPI stuff during a
	 * potentially bad time, such as a timer interrupt.
	 */
	asus->led_workqueue = create_singlethread_workqueue("led_workqueue");
	if (!asus->led_workqueue)
		return -ENOMEM;

	if (asus->wled_type == TYPE_LED)
		r = asus_led_register(asus, &asus->wled, "asus::wlan",
				      METHOD_WLAN);
	if (r)
		goto error;
	if (asus->bled_type == TYPE_LED)
		r = asus_led_register(asus, &asus->bled, "asus::bluetooth",
				      METHOD_BLUETOOTH);
	if (r)
		goto error;
	r = asus_led_register(asus, &asus->mled, "asus::mail", METHOD_MLED);
	if (r)
		goto error;
	r = asus_led_register(asus, &asus->tled, "asus::touchpad", METHOD_TLED);
	if (r)
		goto error;
	r = asus_led_register(asus, &asus->rled, "asus::record", METHOD_RLED);
	if (r)
		goto error;
	r = asus_led_register(asus, &asus->pled, "asus::phone", METHOD_PLED);
	if (r)
		goto error;
	r = asus_led_register(asus, &asus->gled, "asus::gaming", METHOD_GLED);
	if (r)
		goto error;
	if (!acpi_check_handle(asus->handle, METHOD_KBD_LIGHT_SET, NULL) &&
	    !acpi_check_handle(asus->handle, METHOD_KBD_LIGHT_GET, NULL)) {
		struct asus_led *led = &asus->kled;
		struct led_classdev *cdev = &led->led;

		led->asus = asus;

		INIT_WORK(&led->work, asus_kled_cdev_update);
		cdev->name = "asus::kbd_backlight";
		cdev->brightness_set = asus_kled_cdev_set;
		cdev->brightness_get = asus_kled_cdev_get;
		cdev->max_brightness = 3;
		r = led_classdev_register(&asus->platform_device->dev, cdev);
	}
error:
	if (r)
		asus_led_exit(asus);
	return r;
}