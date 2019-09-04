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
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct backlight_device {TYPE_2__ dev; } ;
struct adp5520_bl {TYPE_1__* pdata; int /*<<< orphan*/  master; } ;
struct TYPE_3__ {scalar_t__ en_ambl_sens; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5520_BL_EN ; 
 int /*<<< orphan*/  ADP5520_MODE_STATUS ; 
 int /*<<< orphan*/  adp5520_bl_attr_group ; 
 int /*<<< orphan*/  adp5520_clr_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adp5520_bl* bl_get_data (struct backlight_device*) ; 
 struct backlight_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5520_bl_remove(struct platform_device *pdev)
{
	struct backlight_device *bl = platform_get_drvdata(pdev);
	struct adp5520_bl *data = bl_get_data(bl);

	adp5520_clr_bits(data->master, ADP5520_MODE_STATUS, ADP5520_BL_EN);

	if (data->pdata->en_ambl_sens)
		sysfs_remove_group(&bl->dev.kobj,
				&adp5520_bl_attr_group);

	return 0;
}