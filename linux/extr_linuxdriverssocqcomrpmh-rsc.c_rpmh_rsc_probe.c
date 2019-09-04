#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  batch_cache; int /*<<< orphan*/  cache; int /*<<< orphan*/  cache_lock; } ;
struct rsc_drv {TYPE_2__ client; TYPE_1__* tcs; scalar_t__ name; int /*<<< orphan*/  id; int /*<<< orphan*/  tcs_in_use; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 size_t ACTIVE_TCS ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  MAX_TCS_NR ; 
 int /*<<< orphan*/  RSC_DRV_IRQ_ENABLE ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmd_db_ready () ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 scalar_t__ dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct rsc_drv*) ; 
 struct rsc_drv* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (TYPE_3__*) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int,scalar_t__,struct rsc_drv*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int rpmh_probe_tcs_config (struct platform_device*,struct rsc_drv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcs_tx_done ; 
 int /*<<< orphan*/  write_tcs_reg (struct rsc_drv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpmh_rsc_probe(struct platform_device *pdev)
{
	struct device_node *dn = pdev->dev.of_node;
	struct rsc_drv *drv;
	int ret, irq;

	/*
	 * Even though RPMh doesn't directly use cmd-db, all of its children
	 * do. To avoid adding this check to our children we'll do it now.
	 */
	ret = cmd_db_ready();
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Command DB not available (%d)\n",
									ret);
		return ret;
	}

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	ret = of_property_read_u32(dn, "qcom,drv-id", &drv->id);
	if (ret)
		return ret;

	drv->name = of_get_property(dn, "label", NULL);
	if (!drv->name)
		drv->name = dev_name(&pdev->dev);

	ret = rpmh_probe_tcs_config(pdev, drv);
	if (ret)
		return ret;

	spin_lock_init(&drv->lock);
	bitmap_zero(drv->tcs_in_use, MAX_TCS_NR);

	irq = platform_get_irq(pdev, drv->id);
	if (irq < 0)
		return irq;

	ret = devm_request_irq(&pdev->dev, irq, tcs_tx_done,
			       IRQF_TRIGGER_HIGH | IRQF_NO_SUSPEND,
			       drv->name, drv);
	if (ret)
		return ret;

	/* Enable the active TCS to send requests immediately */
	write_tcs_reg(drv, RSC_DRV_IRQ_ENABLE, 0, drv->tcs[ACTIVE_TCS].mask);

	spin_lock_init(&drv->client.cache_lock);
	INIT_LIST_HEAD(&drv->client.cache);
	INIT_LIST_HEAD(&drv->client.batch_cache);

	dev_set_drvdata(&pdev->dev, drv);

	return devm_of_platform_populate(&pdev->dev);
}