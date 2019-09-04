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
struct da9052_bl {int brightness; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_WLEDS_ON ; 
 struct da9052_bl* bl_get_data (struct backlight_device*) ; 
 int da9052_adjust_wled_brightness (struct da9052_bl*) ; 

__attribute__((used)) static int da9052_backlight_update_status(struct backlight_device *bl)
{
	int brightness = bl->props.brightness;
	struct da9052_bl *wleds = bl_get_data(bl);

	wleds->brightness = brightness;
	wleds->state = DA9052_WLEDS_ON;

	return da9052_adjust_wled_brightness(wleds);
}