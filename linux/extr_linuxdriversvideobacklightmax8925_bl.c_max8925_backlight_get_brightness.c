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
struct max8925_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c; } ;
struct max8925_backlight_data {int current_brightness; int /*<<< orphan*/  reg_cntl; struct max8925_chip* chip; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct max8925_backlight_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int max8925_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8925_backlight_get_brightness(struct backlight_device *bl)
{
	struct max8925_backlight_data *data = bl_get_data(bl);
	struct max8925_chip *chip = data->chip;
	int ret;

	ret = max8925_reg_read(chip->i2c, data->reg_cntl);
	if (ret < 0)
		return -EINVAL;
	data->current_brightness = ret;
	dev_dbg(chip->dev, "get brightness %d\n", data->current_brightness);
	return ret;
}