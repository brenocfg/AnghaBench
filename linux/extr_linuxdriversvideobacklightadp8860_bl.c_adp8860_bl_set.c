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
struct i2c_client {int dummy; } ;
struct backlight_device {int dummy; } ;
struct adp8860_bl {int cached_daylight_max; int current_brightness; scalar_t__ en_ambl_sens; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP8860_BLMX1 ; 
 int ADP8860_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  ADP8860_MDCR ; 
 int /*<<< orphan*/  CMP_AUTOEN ; 
 int /*<<< orphan*/  DIM_EN ; 
 int adp8860_clr_bits (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adp8860_set_bits (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adp8860_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct adp8860_bl* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int adp8860_bl_set(struct backlight_device *bl, int brightness)
{
	struct adp8860_bl *data = bl_get_data(bl);
	struct i2c_client *client = data->client;
	int ret = 0;

	if (data->en_ambl_sens) {
		if ((brightness > 0) && (brightness < ADP8860_MAX_BRIGHTNESS)) {
			/* Disable Ambient Light auto adjust */
			ret |= adp8860_clr_bits(client, ADP8860_MDCR,
					CMP_AUTOEN);
			ret |= adp8860_write(client, ADP8860_BLMX1, brightness);
		} else {
			/*
			 * MAX_BRIGHTNESS -> Enable Ambient Light auto adjust
			 * restore daylight l1 sysfs brightness
			 */
			ret |= adp8860_write(client, ADP8860_BLMX1,
					 data->cached_daylight_max);
			ret |= adp8860_set_bits(client, ADP8860_MDCR,
					 CMP_AUTOEN);
		}
	} else
		ret |= adp8860_write(client, ADP8860_BLMX1, brightness);

	if (data->current_brightness && brightness == 0)
		ret |= adp8860_set_bits(client,
				ADP8860_MDCR, DIM_EN);
	else if (data->current_brightness == 0 && brightness)
		ret |= adp8860_clr_bits(client,
				ADP8860_MDCR, DIM_EN);

	if (!ret)
		data->current_brightness = brightness;

	return ret;
}