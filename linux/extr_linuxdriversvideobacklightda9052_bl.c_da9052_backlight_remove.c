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
struct platform_device {int dummy; } ;
struct da9052_bl {int /*<<< orphan*/  state; scalar_t__ brightness; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_WLEDS_OFF ; 
 struct da9052_bl* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  da9052_adjust_wled_brightness (struct da9052_bl*) ; 
 struct backlight_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int da9052_backlight_remove(struct platform_device *pdev)
{
	struct backlight_device *bl = platform_get_drvdata(pdev);
	struct da9052_bl *wleds = bl_get_data(bl);

	wleds->brightness = 0;
	wleds->state = DA9052_WLEDS_OFF;
	da9052_adjust_wled_brightness(wleds);

	return 0;
}