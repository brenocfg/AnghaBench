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
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_4__ {scalar_t__ kbdlight; } ;
struct TYPE_3__ {int /*<<< orphan*/  led_classdev; } ;

/* Variables and functions */
#define  TP_HKEY_EV_BRGHT_DOWN 132 
#define  TP_HKEY_EV_BRGHT_UP 131 
 unsigned int const TP_HKEY_EV_KBD_LIGHT ; 
#define  TP_HKEY_EV_VOL_DOWN 130 
#define  TP_HKEY_EV_VOL_MUTE 129 
#define  TP_HKEY_EV_VOL_UP 128 
 scalar_t__ alsa_card ; 
 scalar_t__ ibm_backlight_device ; 
 int kbdlight_brightness ; 
 int /*<<< orphan*/  kbdlight_mutex ; 
 int kbdlight_sysfs_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_notify_brightness_hw_changed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ tp_features ; 
 int /*<<< orphan*/  tpacpi_brightness_notify_change () ; 
 TYPE_1__ tpacpi_led_kbdlight ; 
 int /*<<< orphan*/  volume_alsa_notify_change () ; 

__attribute__((used)) static void tpacpi_driver_event(const unsigned int hkey_event)
{
	if (ibm_backlight_device) {
		switch (hkey_event) {
		case TP_HKEY_EV_BRGHT_UP:
		case TP_HKEY_EV_BRGHT_DOWN:
			tpacpi_brightness_notify_change();
		}
	}
	if (alsa_card) {
		switch (hkey_event) {
		case TP_HKEY_EV_VOL_UP:
		case TP_HKEY_EV_VOL_DOWN:
		case TP_HKEY_EV_VOL_MUTE:
			volume_alsa_notify_change();
		}
	}
	if (tp_features.kbdlight && hkey_event == TP_HKEY_EV_KBD_LIGHT) {
		enum led_brightness brightness;

		mutex_lock(&kbdlight_mutex);

		/*
		 * Check the brightness actually changed, setting the brightness
		 * through kbdlight_set_level() also triggers this event.
		 */
		brightness = kbdlight_sysfs_get(NULL);
		if (kbdlight_brightness != brightness) {
			kbdlight_brightness = brightness;
			led_classdev_notify_brightness_hw_changed(
				&tpacpi_led_kbdlight.led_classdev, brightness);
		}

		mutex_unlock(&kbdlight_mutex);
	}
}