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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_2__ dev; } ;
struct lp8788_bl {struct backlight_device* bl_dev; } ;
struct TYPE_3__ {scalar_t__ brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  lp8788_attr_group ; 
 int /*<<< orphan*/  lp8788_backlight_unregister (struct lp8788_bl*) ; 
 struct lp8788_bl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp8788_backlight_remove(struct platform_device *pdev)
{
	struct lp8788_bl *bl = platform_get_drvdata(pdev);
	struct backlight_device *bl_dev = bl->bl_dev;

	bl_dev->props.brightness = 0;
	backlight_update_status(bl_dev);
	sysfs_remove_group(&pdev->dev.kobj, &lp8788_attr_group);
	lp8788_backlight_unregister(bl);

	return 0;
}