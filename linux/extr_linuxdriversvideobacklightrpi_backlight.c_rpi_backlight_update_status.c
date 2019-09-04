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
struct rpi_backlight {int /*<<< orphan*/  dev; int /*<<< orphan*/  fw; } ;
struct TYPE_2__ {int brightness; scalar_t__ power; scalar_t__ fb_blank; int state; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  brightness ;

/* Variables and functions */
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 int EAGAIN ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  RPI_FIRMWARE_FRAMEBUFFER_SET_BACKLIGHT ; 
 struct rpi_backlight* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int rpi_backlight_update_status(struct backlight_device *bl)
{
	struct rpi_backlight *gbl = bl_get_data(bl);
	int brightness = bl->props.brightness;
	int ret;

	if (bl->props.power != FB_BLANK_UNBLANK ||
	    bl->props.fb_blank != FB_BLANK_UNBLANK ||
	    bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	ret = rpi_firmware_property(gbl->fw,
			RPI_FIRMWARE_FRAMEBUFFER_SET_BACKLIGHT,
			&brightness, sizeof(brightness));
	if (ret) {
		dev_err(gbl->dev, "Failed to set brightness\n");
		return ret;
	}

	if (brightness < 0) {
		dev_err(gbl->dev, "Backlight change failed\n");
		return -EAGAIN;
	}

	return 0;
}