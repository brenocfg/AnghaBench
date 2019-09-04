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
typedef  int u8 ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct pandora_private {int /*<<< orphan*/  old_state; } ;
struct backlight_properties {int /*<<< orphan*/  type; void* max_brightness; } ;
struct TYPE_2__ {void* brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  props ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 void* MAX_USER_VALUE ; 
 int /*<<< orphan*/  PANDORABL_WAS_OFF ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  TWL4030_MODULE_INTBR ; 
 int /*<<< orphan*/  TWL_INTBR_PMBR1 ; 
 int /*<<< orphan*/  TWL_MODULE_PWM ; 
 int TWL_PMBR1_PWM0 ; 
 int TWL_PMBR1_PWM0_MUXMASK ; 
 int /*<<< orphan*/  TWL_PWM0_ON ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pandora_private*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct pandora_private* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pandora_backlight_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 int /*<<< orphan*/  twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pandora_backlight_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	struct backlight_device *bl;
	struct pandora_private *priv;
	u8 r;

	priv = devm_kmalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "failed to allocate driver private data\n");
		return -ENOMEM;
	}

	memset(&props, 0, sizeof(props));
	props.max_brightness = MAX_USER_VALUE;
	props.type = BACKLIGHT_RAW;
	bl = devm_backlight_device_register(&pdev->dev, pdev->name, &pdev->dev,
					priv, &pandora_backlight_ops, &props);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		return PTR_ERR(bl);
	}

	platform_set_drvdata(pdev, bl);

	/* 64 cycle period, ON position 0 */
	twl_i2c_write_u8(TWL_MODULE_PWM, 0x80, TWL_PWM0_ON);

	priv->old_state = PANDORABL_WAS_OFF;
	bl->props.brightness = MAX_USER_VALUE;
	backlight_update_status(bl);

	/* enable PWM function in pin mux */
	twl_i2c_read_u8(TWL4030_MODULE_INTBR, &r, TWL_INTBR_PMBR1);
	r &= ~TWL_PMBR1_PWM0_MUXMASK;
	r |= TWL_PMBR1_PWM0;
	twl_i2c_write_u8(TWL4030_MODULE_INTBR, r, TWL_INTBR_PMBR1);

	return 0;
}