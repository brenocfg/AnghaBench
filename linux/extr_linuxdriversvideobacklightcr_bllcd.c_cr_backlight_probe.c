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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ brightness; int /*<<< orphan*/  power; } ;
struct lcd_device {TYPE_1__ props; } ;
struct cr_panel {struct lcd_device* cr_lcd_device; struct lcd_device* cr_backlight_device; } ;
struct backlight_properties {int /*<<< orphan*/  type; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int /*<<< orphan*/  CRVML_DEVICE_LPC ; 
 int CRVML_GPIOEN_BIT ; 
 int /*<<< orphan*/  CRVML_REG_GPIOBAR ; 
 int /*<<< orphan*/  CRVML_REG_GPIOEN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  cr_backlight_ops ; 
 int /*<<< orphan*/  cr_backlight_set_intensity (struct lcd_device*) ; 
 int /*<<< orphan*/  cr_lcd_ops ; 
 int /*<<< orphan*/  cr_lcd_set_power (struct lcd_device*,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct cr_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gpio_bar ; 
 int /*<<< orphan*/  lpc_dev ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cr_panel*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cr_backlight_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	struct backlight_device *bdp;
	struct lcd_device *ldp;
	struct cr_panel *crp;
	u8 dev_en;

	lpc_dev = pci_get_device(PCI_VENDOR_ID_INTEL,
					CRVML_DEVICE_LPC, NULL);
	if (!lpc_dev) {
		pr_err("INTEL CARILLO RANCH LPC not found.\n");
		return -ENODEV;
	}

	pci_read_config_byte(lpc_dev, CRVML_REG_GPIOEN, &dev_en);
	if (!(dev_en & CRVML_GPIOEN_BIT)) {
		pr_err("Carillo Ranch GPIO device was not enabled.\n");
		pci_dev_put(lpc_dev);
		return -ENODEV;
	}

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_RAW;
	bdp = devm_backlight_device_register(&pdev->dev, "cr-backlight",
					&pdev->dev, NULL, &cr_backlight_ops,
					&props);
	if (IS_ERR(bdp)) {
		pci_dev_put(lpc_dev);
		return PTR_ERR(bdp);
	}

	ldp = devm_lcd_device_register(&pdev->dev, "cr-lcd", &pdev->dev, NULL,
					&cr_lcd_ops);
	if (IS_ERR(ldp)) {
		pci_dev_put(lpc_dev);
		return PTR_ERR(ldp);
	}

	pci_read_config_dword(lpc_dev, CRVML_REG_GPIOBAR,
			      &gpio_bar);
	gpio_bar &= ~0x3F;

	crp = devm_kzalloc(&pdev->dev, sizeof(*crp), GFP_KERNEL);
	if (!crp) {
		pci_dev_put(lpc_dev);
		return -ENOMEM;
	}

	crp->cr_backlight_device = bdp;
	crp->cr_lcd_device = ldp;
	crp->cr_backlight_device->props.power = FB_BLANK_UNBLANK;
	crp->cr_backlight_device->props.brightness = 0;
	cr_backlight_set_intensity(crp->cr_backlight_device);
	cr_lcd_set_power(crp->cr_lcd_device, FB_BLANK_UNBLANK);

	platform_set_drvdata(pdev, crp);

	return 0;
}