#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int base; int npwm; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; TYPE_2__* dev; } ;
struct pwm_omap_dmtimer_chip {int /*<<< orphan*/ * dm_timer; struct omap_dm_timer_ops const* pdata; TYPE_1__ chip; int /*<<< orphan*/  mutex; struct platform_device* dm_timer_pdev; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct omap_dm_timer_ops {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_source ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_prescaler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* request_by_node ) (struct device_node*) ;int /*<<< orphan*/  write_counter; int /*<<< orphan*/  set_pwm; int /*<<< orphan*/  set_match; int /*<<< orphan*/  set_load; int /*<<< orphan*/  start; int /*<<< orphan*/  get_fclk; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;
struct dmtimer_platform_data {struct omap_dm_timer_ops* timer_ops; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  pwm_omap_dmtimer ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct dmtimer_platform_data* dev_get_platdata (TYPE_2__*) ; 
 struct pwm_omap_dmtimer_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pwm_omap_dmtimer_chip*) ; 
 scalar_t__ pm_runtime_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pwm_omap_dmtimer_ops ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/ * stub1 (struct device_node*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_omap_dmtimer_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *timer;
	struct platform_device *timer_pdev;
	struct pwm_omap_dmtimer_chip *omap;
	struct dmtimer_platform_data *timer_pdata;
	const struct omap_dm_timer_ops *pdata;
	pwm_omap_dmtimer *dm_timer;
	u32 v;
	int ret = 0;

	timer = of_parse_phandle(np, "ti,timers", 0);
	if (!timer)
		return -ENODEV;

	timer_pdev = of_find_device_by_node(timer);
	if (!timer_pdev) {
		dev_err(&pdev->dev, "Unable to find Timer pdev\n");
		ret = -ENODEV;
		goto put;
	}

	timer_pdata = dev_get_platdata(&timer_pdev->dev);
	if (!timer_pdata) {
		dev_dbg(&pdev->dev,
			 "dmtimer pdata structure NULL, deferring probe\n");
		ret = -EPROBE_DEFER;
		goto put;
	}

	pdata = timer_pdata->timer_ops;

	if (!pdata || !pdata->request_by_node ||
	    !pdata->free ||
	    !pdata->enable ||
	    !pdata->disable ||
	    !pdata->get_fclk ||
	    !pdata->start ||
	    !pdata->stop ||
	    !pdata->set_load ||
	    !pdata->set_match ||
	    !pdata->set_pwm ||
	    !pdata->set_prescaler ||
	    !pdata->write_counter) {
		dev_err(&pdev->dev, "Incomplete dmtimer pdata structure\n");
		ret = -EINVAL;
		goto put;
	}

	if (!of_get_property(timer, "ti,timer-pwm", NULL)) {
		dev_err(&pdev->dev, "Missing ti,timer-pwm capability\n");
		ret = -ENODEV;
		goto put;
	}

	dm_timer = pdata->request_by_node(timer);
	if (!dm_timer) {
		ret = -EPROBE_DEFER;
		goto put;
	}

put:
	of_node_put(timer);
	if (ret < 0)
		return ret;

	omap = devm_kzalloc(&pdev->dev, sizeof(*omap), GFP_KERNEL);
	if (!omap) {
		pdata->free(dm_timer);
		return -ENOMEM;
	}

	omap->pdata = pdata;
	omap->dm_timer = dm_timer;
	omap->dm_timer_pdev = timer_pdev;

	/*
	 * Ensure that the timer is stopped before we allow PWM core to call
	 * pwm_enable.
	 */
	if (pm_runtime_active(&omap->dm_timer_pdev->dev))
		omap->pdata->stop(omap->dm_timer);

	if (!of_property_read_u32(pdev->dev.of_node, "ti,prescaler", &v))
		omap->pdata->set_prescaler(omap->dm_timer, v);

	/* setup dmtimer clock source */
	if (!of_property_read_u32(pdev->dev.of_node, "ti,clock-source", &v))
		omap->pdata->set_source(omap->dm_timer, v);

	omap->chip.dev = &pdev->dev;
	omap->chip.ops = &pwm_omap_dmtimer_ops;
	omap->chip.base = -1;
	omap->chip.npwm = 1;
	omap->chip.of_xlate = of_pwm_xlate_with_flags;
	omap->chip.of_pwm_n_cells = 3;

	mutex_init(&omap->mutex);

	ret = pwmchip_add(&omap->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register PWM\n");
		omap->pdata->free(omap->dm_timer);
		return ret;
	}

	platform_set_drvdata(pdev, omap);

	return 0;
}