#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct da9052_bl {TYPE_5__* da9052; int /*<<< orphan*/  state; int /*<<< orphan*/  led_reg; scalar_t__ brightness; } ;
struct backlight_properties {void* max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {scalar_t__ brightness; void* max_brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 void* DA9052_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  DA9052_WLEDS_OFF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int da9052_adjust_wled_brightness (struct da9052_bl*) ; 
 int /*<<< orphan*/  da9052_backlight_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 TYPE_5__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct backlight_device* devm_backlight_device_register (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da9052_bl*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct da9052_bl* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* platform_get_device_id (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 

__attribute__((used)) static int da9052_backlight_probe(struct platform_device *pdev)
{
	struct backlight_device *bl;
	struct backlight_properties props;
	struct da9052_bl *wleds;

	wleds = devm_kzalloc(&pdev->dev, sizeof(struct da9052_bl), GFP_KERNEL);
	if (!wleds)
		return -ENOMEM;

	wleds->da9052 = dev_get_drvdata(pdev->dev.parent);
	wleds->brightness = 0;
	wleds->led_reg = platform_get_device_id(pdev)->driver_data;
	wleds->state = DA9052_WLEDS_OFF;

	props.type = BACKLIGHT_RAW;
	props.max_brightness = DA9052_MAX_BRIGHTNESS;

	bl = devm_backlight_device_register(&pdev->dev, pdev->name,
					wleds->da9052->dev, wleds,
					&da9052_backlight_ops, &props);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "Failed to register backlight\n");
		return PTR_ERR(bl);
	}

	bl->props.max_brightness = DA9052_MAX_BRIGHTNESS;
	bl->props.brightness = 0;
	platform_set_drvdata(pdev, bl);

	return da9052_adjust_wled_brightness(wleds);
}