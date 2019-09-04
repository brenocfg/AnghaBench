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
struct lcd_device {int /*<<< orphan*/  dev; } ;
struct clps711x_fb_info {int /*<<< orphan*/  lcd_pwr; } ;

/* Variables and functions */
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct clps711x_fb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ regulator_is_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clps711x_lcd_set_power(struct lcd_device *lcddev, int blank)
{
	struct clps711x_fb_info *cfb = dev_get_drvdata(&lcddev->dev);

	if (!IS_ERR_OR_NULL(cfb->lcd_pwr)) {
		if (blank == FB_BLANK_UNBLANK) {
			if (!regulator_is_enabled(cfb->lcd_pwr))
				return regulator_enable(cfb->lcd_pwr);
		} else {
			if (regulator_is_enabled(cfb->lcd_pwr))
				return regulator_disable(cfb->lcd_pwr);
		}
	}

	return 0;
}