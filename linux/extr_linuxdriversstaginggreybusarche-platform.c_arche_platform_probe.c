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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct arche_platform_drvdata {int svc_reset_gpio; int svc_sysboot_gpio; int svc_refclk_req; int wake_detect_gpio; int /*<<< orphan*/  platform_state_mutex; TYPE_1__ pm_notifier; int /*<<< orphan*/  wake_detect_irq; int /*<<< orphan*/  wake_lock; struct device* dev; int /*<<< orphan*/  num_apbs; int /*<<< orphan*/  svc_ref_clk; int /*<<< orphan*/  is_reset_act_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHE_PLATFORM_STATE_OFF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WD_STATE_IDLE ; 
 int arche_platform_coldboot_seq (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  arche_platform_pm_notifier ; 
 int /*<<< orphan*/  arche_platform_set_state (struct arche_platform_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arche_platform_set_wake_detect_state (struct arche_platform_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arche_platform_wd_irq ; 
 int /*<<< orphan*/  arche_platform_wd_irq_en (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  arche_platform_wd_irq_thread ; 
 int /*<<< orphan*/  dev_attr_state ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int devm_gpio_request (struct device*,int,char*) ; 
 struct arche_platform_drvdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int gpio_direction_input (int) ; 
 int gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_to_irq (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_child_count (struct device_node*) ; 
 void* of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct arche_platform_drvdata*) ; 
 int register_pm_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arche_platform_probe(struct platform_device *pdev)
{
	struct arche_platform_drvdata *arche_pdata;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;

	arche_pdata = devm_kzalloc(&pdev->dev, sizeof(*arche_pdata),
				   GFP_KERNEL);
	if (!arche_pdata)
		return -ENOMEM;

	/* setup svc reset gpio */
	arche_pdata->is_reset_act_hi = of_property_read_bool(np,
							     "svc,reset-active-high");
	arche_pdata->svc_reset_gpio = of_get_named_gpio(np,
							"svc,reset-gpio",
							0);
	if (!gpio_is_valid(arche_pdata->svc_reset_gpio)) {
		dev_err(dev, "failed to get reset-gpio\n");
		return arche_pdata->svc_reset_gpio;
	}
	ret = devm_gpio_request(dev, arche_pdata->svc_reset_gpio, "svc-reset");
	if (ret) {
		dev_err(dev, "failed to request svc-reset gpio:%d\n", ret);
		return ret;
	}
	ret = gpio_direction_output(arche_pdata->svc_reset_gpio,
				    arche_pdata->is_reset_act_hi);
	if (ret) {
		dev_err(dev, "failed to set svc-reset gpio dir:%d\n", ret);
		return ret;
	}
	arche_platform_set_state(arche_pdata, ARCHE_PLATFORM_STATE_OFF);

	arche_pdata->svc_sysboot_gpio = of_get_named_gpio(np,
							  "svc,sysboot-gpio",
							  0);
	if (!gpio_is_valid(arche_pdata->svc_sysboot_gpio)) {
		dev_err(dev, "failed to get sysboot gpio\n");
		return arche_pdata->svc_sysboot_gpio;
	}
	ret = devm_gpio_request(dev, arche_pdata->svc_sysboot_gpio, "sysboot0");
	if (ret) {
		dev_err(dev, "failed to request sysboot0 gpio:%d\n", ret);
		return ret;
	}
	ret = gpio_direction_output(arche_pdata->svc_sysboot_gpio, 0);
	if (ret) {
		dev_err(dev, "failed to set svc-reset gpio dir:%d\n", ret);
		return ret;
	}

	/* setup the clock request gpio first */
	arche_pdata->svc_refclk_req = of_get_named_gpio(np,
							"svc,refclk-req-gpio",
							0);
	if (!gpio_is_valid(arche_pdata->svc_refclk_req)) {
		dev_err(dev, "failed to get svc clock-req gpio\n");
		return arche_pdata->svc_refclk_req;
	}
	ret = devm_gpio_request(dev, arche_pdata->svc_refclk_req,
				"svc-clk-req");
	if (ret) {
		dev_err(dev, "failed to request svc-clk-req gpio: %d\n", ret);
		return ret;
	}
	ret = gpio_direction_input(arche_pdata->svc_refclk_req);
	if (ret) {
		dev_err(dev, "failed to set svc-clk-req gpio dir :%d\n", ret);
		return ret;
	}

	/* setup refclk2 to follow the pin */
	arche_pdata->svc_ref_clk = devm_clk_get(dev, "svc_ref_clk");
	if (IS_ERR(arche_pdata->svc_ref_clk)) {
		ret = PTR_ERR(arche_pdata->svc_ref_clk);
		dev_err(dev, "failed to get svc_ref_clk: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, arche_pdata);

	arche_pdata->num_apbs = of_get_child_count(np);
	dev_dbg(dev, "Number of APB's available - %d\n", arche_pdata->num_apbs);

	arche_pdata->wake_detect_gpio = of_get_named_gpio(np,
							  "svc,wake-detect-gpio",
							  0);
	if (arche_pdata->wake_detect_gpio < 0) {
		dev_err(dev, "failed to get wake detect gpio\n");
		return arche_pdata->wake_detect_gpio;
	}

	ret = devm_gpio_request(dev, arche_pdata->wake_detect_gpio,
				"wake detect");
	if (ret) {
		dev_err(dev, "Failed requesting wake_detect gpio %d\n",
			arche_pdata->wake_detect_gpio);
		return ret;
	}

	arche_platform_set_wake_detect_state(arche_pdata, WD_STATE_IDLE);

	arche_pdata->dev = &pdev->dev;

	spin_lock_init(&arche_pdata->wake_lock);
	mutex_init(&arche_pdata->platform_state_mutex);
	arche_pdata->wake_detect_irq =
		gpio_to_irq(arche_pdata->wake_detect_gpio);

	ret = devm_request_threaded_irq(dev, arche_pdata->wake_detect_irq,
					arche_platform_wd_irq,
					arche_platform_wd_irq_thread,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(dev), arche_pdata);
	if (ret) {
		dev_err(dev, "failed to request wake detect IRQ %d\n", ret);
		return ret;
	}
	disable_irq(arche_pdata->wake_detect_irq);

	ret = device_create_file(dev, &dev_attr_state);
	if (ret) {
		dev_err(dev, "failed to create state file in sysfs\n");
		return ret;
	}

	ret = of_platform_populate(np, NULL, NULL, dev);
	if (ret) {
		dev_err(dev, "failed to populate child nodes %d\n", ret);
		goto err_device_remove;
	}

	arche_pdata->pm_notifier.notifier_call = arche_platform_pm_notifier;
	ret = register_pm_notifier(&arche_pdata->pm_notifier);

	if (ret) {
		dev_err(dev, "failed to register pm notifier %d\n", ret);
		goto err_device_remove;
	}

	/* Explicitly power off if requested */
	if (!of_property_read_bool(pdev->dev.of_node, "arche,init-off")) {
		mutex_lock(&arche_pdata->platform_state_mutex);
		ret = arche_platform_coldboot_seq(arche_pdata);
		if (ret) {
			dev_err(dev, "Failed to cold boot svc %d\n", ret);
			goto err_coldboot;
		}
		arche_platform_wd_irq_en(arche_pdata);
		mutex_unlock(&arche_pdata->platform_state_mutex);
	}

	dev_info(dev, "Device registered successfully\n");
	return 0;

err_coldboot:
	mutex_unlock(&arche_pdata->platform_state_mutex);
err_device_remove:
	device_remove_file(&pdev->dev, &dev_attr_state);
	return ret;
}