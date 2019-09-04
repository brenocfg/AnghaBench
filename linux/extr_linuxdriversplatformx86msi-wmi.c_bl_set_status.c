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
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * backlight_map ; 
 int msi_wmi_set_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bl_set_status(struct backlight_device *bd)
{
	int bright = bd->props.brightness;
	if (bright >= ARRAY_SIZE(backlight_map) || bright < 0)
		return -EINVAL;

	/* Instance 0 is "set backlight" */
	return msi_wmi_set_block(0, backlight_map[bright]);
}