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
struct sony_backlight_props {int offset; int cmd_base; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ bl_get_data (struct backlight_device*) ; 
 scalar_t__ sony_call_snc_handle (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int sony_nc_update_status_ng(struct backlight_device *bd)
{
	int value, result;
	struct sony_backlight_props *sdev =
		(struct sony_backlight_props *)bl_get_data(bd);

	value = bd->props.brightness + sdev->offset;
	if (sony_call_snc_handle(sdev->handle, sdev->cmd_base | (value << 0x10),
				&result))
		return -EIO;

	return value;
}