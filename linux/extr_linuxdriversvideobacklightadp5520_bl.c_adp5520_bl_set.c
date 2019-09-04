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
struct device {int dummy; } ;
struct backlight_device {int dummy; } ;
struct adp5520_bl {int cached_daylight_max; int current_brightness; TYPE_1__* pdata; struct device* master; } ;
struct TYPE_2__ {scalar_t__ en_ambl_sens; } ;

/* Variables and functions */
 int ADP5020_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  ADP5520_BL_AUTO_ADJ ; 
 int /*<<< orphan*/  ADP5520_BL_CONTROL ; 
 int /*<<< orphan*/  ADP5520_DAYLIGHT_MAX ; 
 int /*<<< orphan*/  ADP5520_DIM_EN ; 
 int /*<<< orphan*/  ADP5520_MODE_STATUS ; 
 int adp5520_clr_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adp5520_set_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adp5520_write (struct device*,int /*<<< orphan*/ ,int) ; 
 struct adp5520_bl* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int adp5520_bl_set(struct backlight_device *bl, int brightness)
{
	struct adp5520_bl *data = bl_get_data(bl);
	struct device *master = data->master;
	int ret = 0;

	if (data->pdata->en_ambl_sens) {
		if ((brightness > 0) && (brightness < ADP5020_MAX_BRIGHTNESS)) {
			/* Disable Ambient Light auto adjust */
			ret |= adp5520_clr_bits(master, ADP5520_BL_CONTROL,
					ADP5520_BL_AUTO_ADJ);
			ret |= adp5520_write(master, ADP5520_DAYLIGHT_MAX,
					brightness);
		} else {
			/*
			 * MAX_BRIGHTNESS -> Enable Ambient Light auto adjust
			 * restore daylight l3 sysfs brightness
			 */
			ret |= adp5520_write(master, ADP5520_DAYLIGHT_MAX,
					 data->cached_daylight_max);
			ret |= adp5520_set_bits(master, ADP5520_BL_CONTROL,
					 ADP5520_BL_AUTO_ADJ);
		}
	} else {
		ret |= adp5520_write(master, ADP5520_DAYLIGHT_MAX, brightness);
	}

	if (data->current_brightness && brightness == 0)
		ret |= adp5520_set_bits(master,
				ADP5520_MODE_STATUS, ADP5520_DIM_EN);
	else if (data->current_brightness == 0 && brightness)
		ret |= adp5520_clr_bits(master,
				ADP5520_MODE_STATUS, ADP5520_DIM_EN);

	if (!ret)
		data->current_brightness = brightness;

	return ret;
}