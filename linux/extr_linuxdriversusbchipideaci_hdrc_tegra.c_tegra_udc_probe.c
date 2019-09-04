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
struct tegra_udc_soc_info {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  capoffset; int /*<<< orphan*/  usb_phy; int /*<<< orphan*/  flags; } ;
struct tegra_udc {int /*<<< orphan*/  clk; int /*<<< orphan*/  phy; int /*<<< orphan*/  dev; TYPE_1__ data; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_CAPOFFSET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_hdrc_add_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tegra_udc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_usb_get_phy_by_phandle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct tegra_udc_soc_info* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_udc*) ; 
 int /*<<< orphan*/  usb_phy_set_suspend (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tegra_udc_probe(struct platform_device *pdev)
{
	const struct tegra_udc_soc_info *soc;
	struct tegra_udc *udc;
	int err;

	udc = devm_kzalloc(&pdev->dev, sizeof(*udc), GFP_KERNEL);
	if (!udc)
		return -ENOMEM;

	soc = of_device_get_match_data(&pdev->dev);
	if (!soc) {
		dev_err(&pdev->dev, "failed to match OF data\n");
		return -EINVAL;
	}

	udc->phy = devm_usb_get_phy_by_phandle(&pdev->dev, "nvidia,phy", 0);
	if (IS_ERR(udc->phy)) {
		err = PTR_ERR(udc->phy);
		dev_err(&pdev->dev, "failed to get PHY: %d\n", err);
		return err;
	}

	udc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(udc->clk)) {
		err = PTR_ERR(udc->clk);
		dev_err(&pdev->dev, "failed to get clock: %d\n", err);
		return err;
	}

	err = clk_prepare_enable(udc->clk);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to enable clock: %d\n", err);
		return err;
	}

	/*
	 * Tegra's USB PHY driver doesn't implement optional phy_init()
	 * hook, so we have to power on UDC controller before ChipIdea
	 * driver initialization kicks in.
	 */
	usb_phy_set_suspend(udc->phy, 0);

	/* setup and register ChipIdea HDRC device */
	udc->data.name = "tegra-udc";
	udc->data.flags = soc->flags;
	udc->data.usb_phy = udc->phy;
	udc->data.capoffset = DEF_CAPOFFSET;

	udc->dev = ci_hdrc_add_device(&pdev->dev, pdev->resource,
				      pdev->num_resources, &udc->data);
	if (IS_ERR(udc->dev)) {
		err = PTR_ERR(udc->dev);
		dev_err(&pdev->dev, "failed to add HDRC device: %d\n", err);
		goto fail_power_off;
	}

	platform_set_drvdata(pdev, udc);

	return 0;

fail_power_off:
	usb_phy_set_suspend(udc->phy, 1);
	clk_disable_unprepare(udc->clk);
	return err;
}