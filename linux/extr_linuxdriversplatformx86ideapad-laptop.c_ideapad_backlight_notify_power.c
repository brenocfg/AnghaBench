#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ideapad_private {TYPE_1__* adev; struct backlight_device* blightdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_2__ props; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  VPCCMD_R_BL_POWER ; 
 scalar_t__ read_ec_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void ideapad_backlight_notify_power(struct ideapad_private *priv)
{
	unsigned long power;
	struct backlight_device *blightdev = priv->blightdev;

	if (!blightdev)
		return;
	if (read_ec_data(priv->adev->handle, VPCCMD_R_BL_POWER, &power))
		return;
	blightdev->props.power = power ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
}