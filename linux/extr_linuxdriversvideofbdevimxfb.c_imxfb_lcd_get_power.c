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
struct imxfb_info {int /*<<< orphan*/  lcd_pwr; } ;

/* Variables and functions */
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 struct imxfb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_is_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imxfb_lcd_get_power(struct lcd_device *lcddev)
{
	struct imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	if (!IS_ERR(fbi->lcd_pwr) &&
	    !regulator_is_enabled(fbi->lcd_pwr))
		return FB_BLANK_POWERDOWN;

	return FB_BLANK_UNBLANK;
}