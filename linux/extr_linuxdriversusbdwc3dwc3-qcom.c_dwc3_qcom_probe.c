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
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct dwc3_qcom {scalar_t__ mode; int is_suspended; int num_clocks; int /*<<< orphan*/  resets; int /*<<< orphan*/ * clks; TYPE_1__* dwc3; int /*<<< orphan*/  qscratch_base; struct device* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct dwc3_qcom* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_array_get_optional_exclusive (struct device*) ; 
 int dwc3_qcom_clk_init (struct dwc3_qcom*,int /*<<< orphan*/ ) ; 
 int dwc3_qcom_register_extcon (struct dwc3_qcom*) ; 
 int /*<<< orphan*/  dwc3_qcom_select_utmi_clk (struct dwc3_qcom*) ; 
 int dwc3_qcom_setup_irq (struct platform_device*) ; 
 int /*<<< orphan*/  dwc3_qcom_vbus_overrride_enable (struct dwc3_qcom*,int) ; 
 int /*<<< orphan*/  of_count_phandle_with_args (struct device_node*,char*,char*) ; 
 TYPE_1__* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dwc3_qcom*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_get_dr_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dwc3_qcom_probe(struct platform_device *pdev)
{
	struct device_node	*np = pdev->dev.of_node, *dwc3_np;
	struct device		*dev = &pdev->dev;
	struct dwc3_qcom	*qcom;
	struct resource		*res;
	int			ret, i;
	bool			ignore_pipe_clk;

	qcom = devm_kzalloc(&pdev->dev, sizeof(*qcom), GFP_KERNEL);
	if (!qcom)
		return -ENOMEM;

	platform_set_drvdata(pdev, qcom);
	qcom->dev = &pdev->dev;

	qcom->resets = devm_reset_control_array_get_optional_exclusive(dev);
	if (IS_ERR(qcom->resets)) {
		ret = PTR_ERR(qcom->resets);
		dev_err(&pdev->dev, "failed to get resets, err=%d\n", ret);
		return ret;
	}

	ret = reset_control_assert(qcom->resets);
	if (ret) {
		dev_err(&pdev->dev, "failed to assert resets, err=%d\n", ret);
		return ret;
	}

	usleep_range(10, 1000);

	ret = reset_control_deassert(qcom->resets);
	if (ret) {
		dev_err(&pdev->dev, "failed to deassert resets, err=%d\n", ret);
		goto reset_assert;
	}

	ret = dwc3_qcom_clk_init(qcom, of_count_phandle_with_args(np,
						"clocks", "#clock-cells"));
	if (ret) {
		dev_err(dev, "failed to get clocks\n");
		goto reset_assert;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	qcom->qscratch_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(qcom->qscratch_base)) {
		dev_err(dev, "failed to map qscratch, err=%d\n", ret);
		ret = PTR_ERR(qcom->qscratch_base);
		goto clk_disable;
	}

	ret = dwc3_qcom_setup_irq(pdev);
	if (ret)
		goto clk_disable;

	dwc3_np = of_get_child_by_name(np, "dwc3");
	if (!dwc3_np) {
		dev_err(dev, "failed to find dwc3 core child\n");
		ret = -ENODEV;
		goto clk_disable;
	}

	/*
	 * Disable pipe_clk requirement if specified. Used when dwc3
	 * operates without SSPHY and only HS/FS/LS modes are supported.
	 */
	ignore_pipe_clk = device_property_read_bool(dev,
				"qcom,select-utmi-as-pipe-clk");
	if (ignore_pipe_clk)
		dwc3_qcom_select_utmi_clk(qcom);

	ret = of_platform_populate(np, NULL, NULL, dev);
	if (ret) {
		dev_err(dev, "failed to register dwc3 core - %d\n", ret);
		goto clk_disable;
	}

	qcom->dwc3 = of_find_device_by_node(dwc3_np);
	if (!qcom->dwc3) {
		dev_err(&pdev->dev, "failed to get dwc3 platform device\n");
		ret = -ENODEV;
		goto depopulate;
	}

	qcom->mode = usb_get_dr_mode(&qcom->dwc3->dev);

	/* enable vbus override for device mode */
	if (qcom->mode == USB_DR_MODE_PERIPHERAL)
		dwc3_qcom_vbus_overrride_enable(qcom, true);

	/* register extcon to override sw_vbus on Vbus change later */
	ret = dwc3_qcom_register_extcon(qcom);
	if (ret)
		goto depopulate;

	device_init_wakeup(&pdev->dev, 1);
	qcom->is_suspended = false;
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_forbid(dev);

	return 0;

depopulate:
	of_platform_depopulate(&pdev->dev);
clk_disable:
	for (i = qcom->num_clocks - 1; i >= 0; i--) {
		clk_disable_unprepare(qcom->clks[i]);
		clk_put(qcom->clks[i]);
	}
reset_assert:
	reset_control_assert(qcom->resets);

	return ret;
}