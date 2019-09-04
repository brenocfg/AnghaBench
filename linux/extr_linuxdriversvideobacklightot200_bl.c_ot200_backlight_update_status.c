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
struct ot200_backlight_data {int current_brightness; } ;
struct TYPE_2__ {int brightness; int state; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int BL_CORE_FBBLANK ; 
 scalar_t__ MAX_COMP2 ; 
 int /*<<< orphan*/  MFGPT_REG_CMP1 ; 
 int /*<<< orphan*/  MFGPT_REG_COUNTER ; 
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 scalar_t__ MFGPT_SETUP_CNTEN ; 
 struct ot200_backlight_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  cs5535_mfgpt_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* dim_table ; 
 int /*<<< orphan*/  pwm_timer ; 

__attribute__((used)) static int ot200_backlight_update_status(struct backlight_device *bl)
{
	struct ot200_backlight_data *data = bl_get_data(bl);
	int brightness = bl->props.brightness;

	if (bl->props.state & BL_CORE_FBBLANK)
		brightness = 0;

	/* enable or disable PWM timer */
	if (brightness == 0)
		cs5535_mfgpt_write(pwm_timer, MFGPT_REG_SETUP, 0);
	else if (data->current_brightness == 0) {
		cs5535_mfgpt_write(pwm_timer, MFGPT_REG_COUNTER, 0);
		cs5535_mfgpt_write(pwm_timer, MFGPT_REG_SETUP,
			MFGPT_SETUP_CNTEN);
	}

	/* apply new brightness value */
	cs5535_mfgpt_write(pwm_timer, MFGPT_REG_CMP1,
		MAX_COMP2 - dim_table[brightness]);
	data->current_brightness = brightness;

	return 0;
}