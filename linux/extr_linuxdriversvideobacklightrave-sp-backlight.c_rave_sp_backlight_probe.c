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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct backlight_device* devm_backlight_device_register (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rave_sp_backlight_ops ; 
 int /*<<< orphan*/  rave_sp_backlight_props ; 

__attribute__((used)) static int rave_sp_backlight_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct backlight_device *bd;

	bd = devm_backlight_device_register(dev, pdev->name, dev->parent,
					    dev_get_drvdata(dev->parent),
					    &rave_sp_backlight_ops,
					    &rave_sp_backlight_props);
	if (IS_ERR(bd))
		return PTR_ERR(bd);

	backlight_update_status(bd);

	return 0;
}