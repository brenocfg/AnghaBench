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
struct mx3fb_data {int backlight_level; } ;
struct TYPE_2__ {int brightness; scalar_t__ power; scalar_t__ fb_blank; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ FB_BLANK_UNBLANK ; 
 struct mx3fb_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  sdc_set_brightness (struct mx3fb_data*,int) ; 

__attribute__((used)) static int mx3fb_bl_update_status(struct backlight_device *bl)
{
	struct mx3fb_data *fbd = bl_get_data(bl);
	int brightness = bl->props.brightness;

	if (bl->props.power != FB_BLANK_UNBLANK)
		brightness = 0;
	if (bl->props.fb_blank != FB_BLANK_UNBLANK)
		brightness = 0;

	fbd->backlight_level = (fbd->backlight_level & ~0xFF) | brightness;

	sdc_set_brightness(fbd, fbd->backlight_level);

	return 0;
}