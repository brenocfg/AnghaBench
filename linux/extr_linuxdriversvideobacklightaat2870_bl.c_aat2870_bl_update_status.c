#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int brightness; int max_brightness; scalar_t__ power; int state; } ;
struct backlight_device {TYPE_3__ props; int /*<<< orphan*/  dev; } ;
struct aat2870_data {int (* write ) (struct aat2870_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct aat2870_bl_driver_data {int brightness; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAT2870_BLM ; 
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 int EINVAL ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int aat2870_bl_disable (struct aat2870_bl_driver_data*) ; 
 int aat2870_bl_enable (struct aat2870_bl_driver_data*) ; 
 scalar_t__ aat2870_brightness (struct aat2870_bl_driver_data*,int) ; 
 struct aat2870_bl_driver_data* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct aat2870_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int stub1 (struct aat2870_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aat2870_bl_update_status(struct backlight_device *bd)
{
	struct aat2870_bl_driver_data *aat2870_bl = bl_get_data(bd);
	struct aat2870_data *aat2870 =
			dev_get_drvdata(aat2870_bl->pdev->dev.parent);
	int brightness = bd->props.brightness;
	int ret;

	if ((brightness < 0) || (bd->props.max_brightness < brightness)) {
		dev_err(&bd->dev, "invalid brightness, %d\n", brightness);
		return -EINVAL;
	}

	dev_dbg(&bd->dev, "brightness=%d, power=%d, state=%d\n",
		 bd->props.brightness, bd->props.power, bd->props.state);

	if ((bd->props.power != FB_BLANK_UNBLANK) ||
			(bd->props.state & BL_CORE_FBBLANK) ||
			(bd->props.state & BL_CORE_SUSPENDED))
		brightness = 0;

	ret = aat2870->write(aat2870, AAT2870_BLM,
			     (u8)aat2870_brightness(aat2870_bl, brightness));
	if (ret < 0)
		return ret;

	if (brightness == 0) {
		ret = aat2870_bl_disable(aat2870_bl);
		if (ret < 0)
			return ret;
	} else if (aat2870_bl->brightness == 0) {
		ret = aat2870_bl_enable(aat2870_bl);
		if (ret < 0)
			return ret;
	}

	aat2870_bl->brightness = brightness;

	return 0;
}