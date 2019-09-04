#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; } ;
struct of_device_id {struct ci_hdrc_imx_platform_flag* data; } ;
struct device_node {int dummy; } ;
struct ci_hdrc_platform_data {int flags; scalar_t__ usb_phy; int /*<<< orphan*/  capoffset; int /*<<< orphan*/  name; } ;
struct ci_hdrc_imx_platform_flag {int flags; } ;
struct ci_hdrc_imx_data {int override_phy_control; int supports_runtime_pm; scalar_t__ ci_pdev; scalar_t__ usbmisc_data; scalar_t__ phy; } ;

/* Variables and functions */
 int CI_HDRC_OVERRIDE_PHY_CONTROL ; 
 int CI_HDRC_SUPPORTS_RUNTIME_PM ; 
 int /*<<< orphan*/  DEF_CAPOFFSET ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ USBPHY_INTERFACE_MODE_ULPI ; 
 scalar_t__ ci_hdrc_add_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ci_hdrc_platform_data*) ; 
 int /*<<< orphan*/  ci_hdrc_imx_dt_ids ; 
 int /*<<< orphan*/  ci_hdrc_remove_device (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_1__*,int) ; 
 struct ci_hdrc_imx_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_usb_get_phy_by_phandle (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_disable_unprepare_clks (TYPE_1__*) ; 
 int imx_get_clks (TYPE_1__*) ; 
 int imx_prepare_enable_clks (TYPE_1__*) ; 
 int imx_usbmisc_init (scalar_t__) ; 
 int imx_usbmisc_init_post (scalar_t__) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ of_usb_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ci_hdrc_imx_data*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_phy_init (scalar_t__) ; 
 scalar_t__ usbmisc_get_init_data (TYPE_1__*) ; 

__attribute__((used)) static int ci_hdrc_imx_probe(struct platform_device *pdev)
{
	struct ci_hdrc_imx_data *data;
	struct ci_hdrc_platform_data pdata = {
		.name		= dev_name(&pdev->dev),
		.capoffset	= DEF_CAPOFFSET,
	};
	int ret;
	const struct of_device_id *of_id;
	const struct ci_hdrc_imx_platform_flag *imx_platform_flag;
	struct device_node *np = pdev->dev.of_node;

	of_id = of_match_device(ci_hdrc_imx_dt_ids, &pdev->dev);
	if (!of_id)
		return -ENODEV;

	imx_platform_flag = of_id->data;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);
	data->usbmisc_data = usbmisc_get_init_data(&pdev->dev);
	if (IS_ERR(data->usbmisc_data))
		return PTR_ERR(data->usbmisc_data);

	ret = imx_get_clks(&pdev->dev);
	if (ret)
		return ret;

	ret = imx_prepare_enable_clks(&pdev->dev);
	if (ret)
		return ret;

	data->phy = devm_usb_get_phy_by_phandle(&pdev->dev, "fsl,usbphy", 0);
	if (IS_ERR(data->phy)) {
		ret = PTR_ERR(data->phy);
		/* Return -EINVAL if no usbphy is available */
		if (ret == -ENODEV)
			ret = -EINVAL;
		goto err_clk;
	}

	pdata.usb_phy = data->phy;

	if ((of_device_is_compatible(np, "fsl,imx53-usb") ||
	     of_device_is_compatible(np, "fsl,imx51-usb")) && pdata.usb_phy &&
	    of_usb_get_phy_mode(np) == USBPHY_INTERFACE_MODE_ULPI) {
		pdata.flags |= CI_HDRC_OVERRIDE_PHY_CONTROL;
		data->override_phy_control = true;
		usb_phy_init(pdata.usb_phy);
	}

	pdata.flags |= imx_platform_flag->flags;
	if (pdata.flags & CI_HDRC_SUPPORTS_RUNTIME_PM)
		data->supports_runtime_pm = true;

	ret = imx_usbmisc_init(data->usbmisc_data);
	if (ret) {
		dev_err(&pdev->dev, "usbmisc init failed, ret=%d\n", ret);
		goto err_clk;
	}

	data->ci_pdev = ci_hdrc_add_device(&pdev->dev,
				pdev->resource, pdev->num_resources,
				&pdata);
	if (IS_ERR(data->ci_pdev)) {
		ret = PTR_ERR(data->ci_pdev);
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"ci_hdrc_add_device failed, err=%d\n", ret);
		goto err_clk;
	}

	ret = imx_usbmisc_init_post(data->usbmisc_data);
	if (ret) {
		dev_err(&pdev->dev, "usbmisc post failed, ret=%d\n", ret);
		goto disable_device;
	}

	if (data->supports_runtime_pm) {
		pm_runtime_set_active(&pdev->dev);
		pm_runtime_enable(&pdev->dev);
	}

	device_set_wakeup_capable(&pdev->dev, true);

	return 0;

disable_device:
	ci_hdrc_remove_device(data->ci_pdev);
err_clk:
	imx_disable_unprepare_clks(&pdev->dev);
	return ret;
}