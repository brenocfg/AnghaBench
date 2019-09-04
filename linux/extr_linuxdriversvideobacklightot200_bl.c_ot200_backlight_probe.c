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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ot200_backlight_data {int current_brightness; } ;
struct backlight_properties {int max_brightness; int brightness; int /*<<< orphan*/  type; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_DIMM ; 
 int /*<<< orphan*/  GPIO_OUTPUT_AUX1 ; 
 int /*<<< orphan*/  GPIO_OUTPUT_ENABLE ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  MAX_COMP2 ; 
 int /*<<< orphan*/  MFGPT_DOMAIN_ANY ; 
 int /*<<< orphan*/  MFGPT_REG_CMP1 ; 
 int /*<<< orphan*/  MFGPT_REG_CMP2 ; 
 int /*<<< orphan*/  MFGPT_REG_SETUP ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  PWM_SETUP ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_mfgpt_alloc_timer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_mfgpt_free_timer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_mfgpt_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ot200_backlight_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 scalar_t__ devm_gpio_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct ot200_backlight_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ot200_backlight_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 int /*<<< orphan*/  pwm_timer ; 

__attribute__((used)) static int ot200_backlight_probe(struct platform_device *pdev)
{
	struct backlight_device *bl;
	struct ot200_backlight_data *data;
	struct backlight_properties props;
	int retval = 0;

	/* request gpio */
	if (devm_gpio_request(&pdev->dev, GPIO_DIMM,
				"ot200 backlight dimmer") < 0) {
		dev_err(&pdev->dev, "failed to request GPIO %d\n", GPIO_DIMM);
		return -ENODEV;
	}

	/* request timer */
	pwm_timer = cs5535_mfgpt_alloc_timer(7, MFGPT_DOMAIN_ANY);
	if (!pwm_timer) {
		dev_err(&pdev->dev, "MFGPT 7 not available\n");
		return -ENODEV;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		retval = -ENOMEM;
		goto error_devm_kzalloc;
	}

	/* setup gpio */
	cs5535_gpio_set(GPIO_DIMM, GPIO_OUTPUT_ENABLE);
	cs5535_gpio_set(GPIO_DIMM, GPIO_OUTPUT_AUX1);

	/* setup timer */
	cs5535_mfgpt_write(pwm_timer, MFGPT_REG_CMP1, 0);
	cs5535_mfgpt_write(pwm_timer, MFGPT_REG_CMP2, MAX_COMP2);
	cs5535_mfgpt_write(pwm_timer, MFGPT_REG_SETUP, PWM_SETUP);

	data->current_brightness = 100;
	props.max_brightness = 100;
	props.brightness = 100;
	props.type = BACKLIGHT_RAW;

	bl = devm_backlight_device_register(&pdev->dev, dev_name(&pdev->dev),
					&pdev->dev, data, &ot200_backlight_ops,
					&props);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		retval = PTR_ERR(bl);
		goto error_devm_kzalloc;
	}

	platform_set_drvdata(pdev, bl);

	return 0;

error_devm_kzalloc:
	cs5535_mfgpt_free_timer(pwm_timer);
	return retval;
}