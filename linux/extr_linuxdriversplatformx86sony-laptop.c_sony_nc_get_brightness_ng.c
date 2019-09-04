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
struct sony_backlight_props {int offset; scalar_t__ cmd_base; int /*<<< orphan*/  handle; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  sony_call_snc_handle (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static int sony_nc_get_brightness_ng(struct backlight_device *bd)
{
	int result;
	struct sony_backlight_props *sdev =
		(struct sony_backlight_props *)bl_get_data(bd);

	sony_call_snc_handle(sdev->handle, sdev->cmd_base + 0x100, &result);

	return (result & 0xff) - sdev->offset;
}