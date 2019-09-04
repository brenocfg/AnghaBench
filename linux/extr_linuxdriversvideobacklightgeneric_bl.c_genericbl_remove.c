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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ brightness; scalar_t__ power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct backlight_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int genericbl_remove(struct platform_device *pdev)
{
	struct backlight_device *bd = platform_get_drvdata(pdev);

	bd->props.power = 0;
	bd->props.brightness = 0;
	backlight_update_status(bd);

	dev_info(&pdev->dev, "Generic Backlight Driver Unloaded\n");
	return 0;
}