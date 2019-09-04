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
struct wm831x_backlight_data {int current_brightness; int /*<<< orphan*/  isink_reg; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int WM831X_CS1_DRIVE ; 
 int WM831X_CS1_ENA ; 
 int WM831X_CS1_ISEL_MASK ; 
 int WM831X_DC4_ENA ; 
 int /*<<< orphan*/  WM831X_DCDC_ENABLE ; 
 struct wm831x_backlight_data* bl_get_data (struct backlight_device*) ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm831x_backlight_set(struct backlight_device *bl, int brightness)
{
	struct wm831x_backlight_data *data = bl_get_data(bl);
	struct wm831x *wm831x = data->wm831x;
	int power_up = !data->current_brightness && brightness;
	int power_down = data->current_brightness && !brightness;
	int ret;

	if (power_up) {
		/* Enable the ISINK */
		ret = wm831x_set_bits(wm831x, data->isink_reg,
				      WM831X_CS1_ENA, WM831X_CS1_ENA);
		if (ret < 0)
			goto err;

		/* Enable the DC-DC */
		ret = wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE,
				      WM831X_DC4_ENA, WM831X_DC4_ENA);
		if (ret < 0)
			goto err;
	}

	if (power_down) {
		/* DCDC first */
		ret = wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE,
				      WM831X_DC4_ENA, 0);
		if (ret < 0)
			goto err;

		/* ISINK */
		ret = wm831x_set_bits(wm831x, data->isink_reg,
				      WM831X_CS1_DRIVE | WM831X_CS1_ENA, 0);
		if (ret < 0)
			goto err;
	}

	/* Set the new brightness */
	ret = wm831x_set_bits(wm831x, data->isink_reg,
			      WM831X_CS1_ISEL_MASK, brightness);
	if (ret < 0)
		goto err;

	if (power_up) {
		/* Drive current through the ISINK */
		ret = wm831x_set_bits(wm831x, data->isink_reg,
				      WM831X_CS1_DRIVE, WM831X_CS1_DRIVE);
		if (ret < 0)
			return ret;
	}

	data->current_brightness = brightness;

	return 0;

err:
	/* If we were in the middle of a power transition always shut down
	 * for safety.
	 */
	if (power_up || power_down) {
		wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE, WM831X_DC4_ENA, 0);
		wm831x_set_bits(wm831x, data->isink_reg, WM831X_CS1_ENA, 0);
	}

	return ret;
}