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
struct TYPE_2__ {int brightness; int max_brightness; } ;
struct backlight_device {int /*<<< orphan*/  dev; TYPE_1__ props; } ;
struct ams369fg06 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  MAX_BRIGHTNESS ; 
 int MIN_BRIGHTNESS ; 
 int ams369fg06_gamma_ctl (struct ams369fg06*,int) ; 
 struct ams369fg06* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int ams369fg06_set_brightness(struct backlight_device *bd)
{
	int ret = 0;
	int brightness = bd->props.brightness;
	struct ams369fg06 *lcd = bl_get_data(bd);

	if (brightness < MIN_BRIGHTNESS ||
		brightness > bd->props.max_brightness) {
		dev_err(&bd->dev, "lcd brightness should be %d to %d.\n",
			MIN_BRIGHTNESS, MAX_BRIGHTNESS);
		return -EINVAL;
	}

	ret = ams369fg06_gamma_ctl(lcd, bd->props.brightness);
	if (ret) {
		dev_err(&bd->dev, "lcd brightness setting failed.\n");
		return -EIO;
	}

	return ret;
}