#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ipaq_micro {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 struct ipaq_micro* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct backlight_device* devm_backlight_device_register (TYPE_1__*,char*,TYPE_1__*,struct ipaq_micro*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  micro_bl_ops ; 
 int /*<<< orphan*/  micro_bl_props ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 

__attribute__((used)) static int micro_backlight_probe(struct platform_device *pdev)
{
	struct backlight_device *bd;
	struct ipaq_micro *micro = dev_get_drvdata(pdev->dev.parent);

	bd = devm_backlight_device_register(&pdev->dev, "ipaq-micro-backlight",
					    &pdev->dev, micro, &micro_bl_ops,
					    &micro_bl_props);
	if (IS_ERR(bd))
		return PTR_ERR(bd);

	platform_set_drvdata(pdev, bd);
	backlight_update_status(bd);

	return 0;
}