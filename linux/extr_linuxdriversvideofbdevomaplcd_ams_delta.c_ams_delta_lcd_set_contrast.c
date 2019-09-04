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
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int AMS_DELTA_MAX_CONTRAST ; 
 int /*<<< orphan*/  OMAP_PWL_ENABLE ; 
 int ams_delta_lcd ; 
 int /*<<< orphan*/  omap_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ams_delta_lcd_set_contrast(struct lcd_device *dev, int value)
{
	if ((value >= 0) && (value <= AMS_DELTA_MAX_CONTRAST)) {
		omap_writeb(value, OMAP_PWL_ENABLE);
		ams_delta_lcd &= ~AMS_DELTA_MAX_CONTRAST;
		ams_delta_lcd |= value;
	}
	return 0;
}