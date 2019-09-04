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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OT_EC_BL_BRIGHTNESS_ADDRESS ; 
 scalar_t__ OT_EC_BL_BRIGHTNESS_MAX ; 
 int /*<<< orphan*/  OT_EC_BL_CONTROL_ADDRESS ; 
 scalar_t__ OT_EC_BL_CONTROL_ON_DATA ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int set_backlight_brightness(struct backlight_device *b)
{
	u8 percent = (u8) b->props.brightness;
	if (percent < 0 || percent > OT_EC_BL_BRIGHTNESS_MAX)
		return -EINVAL;

	ec_write(OT_EC_BL_BRIGHTNESS_ADDRESS, percent);
	ec_write(OT_EC_BL_CONTROL_ADDRESS, OT_EC_BL_CONTROL_ON_DATA);

	return 0;
}