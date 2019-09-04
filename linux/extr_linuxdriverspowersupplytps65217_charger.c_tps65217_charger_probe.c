#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tps65217_charger {TYPE_1__* dev; struct task_struct* poll_task; struct task_struct* psy; struct tps65217* tps; } ;
struct tps65217 {int dummy; } ;
struct task_struct {int dummy; } ;
struct power_supply_config {struct tps65217_charger* drv_data; int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int NUM_CHARGER_IRQS ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct tps65217* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tps65217_charger* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct task_struct* devm_power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int,struct tps65217_charger*),int /*<<< orphan*/ ,char*,struct tps65217_charger*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct tps65217_charger*,char*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps65217_charger*) ; 
 int /*<<< orphan*/  tps65217_charger_desc ; 
 int /*<<< orphan*/  tps65217_charger_irq (int,struct tps65217_charger*) ; 
 int /*<<< orphan*/  tps65217_charger_poll_task ; 
 int tps65217_config_charger (struct tps65217_charger*) ; 

__attribute__((used)) static int tps65217_charger_probe(struct platform_device *pdev)
{
	struct tps65217 *tps = dev_get_drvdata(pdev->dev.parent);
	struct tps65217_charger *charger;
	struct power_supply_config cfg = {};
	struct task_struct *poll_task;
	int irq[NUM_CHARGER_IRQS];
	int ret;
	int i;

	charger = devm_kzalloc(&pdev->dev, sizeof(*charger), GFP_KERNEL);
	if (!charger)
		return -ENOMEM;

	platform_set_drvdata(pdev, charger);
	charger->tps = tps;
	charger->dev = &pdev->dev;

	cfg.of_node = pdev->dev.of_node;
	cfg.drv_data = charger;

	charger->psy = devm_power_supply_register(&pdev->dev,
						  &tps65217_charger_desc,
						  &cfg);
	if (IS_ERR(charger->psy)) {
		dev_err(&pdev->dev, "failed: power supply register\n");
		return PTR_ERR(charger->psy);
	}

	irq[0] = platform_get_irq_byname(pdev, "USB");
	irq[1] = platform_get_irq_byname(pdev, "AC");

	ret = tps65217_config_charger(charger);
	if (ret < 0) {
		dev_err(charger->dev, "charger config failed, err %d\n", ret);
		return ret;
	}

	/* Create a polling thread if an interrupt is invalid */
	if (irq[0] < 0 || irq[1] < 0) {
		poll_task = kthread_run(tps65217_charger_poll_task,
					charger, "ktps65217charger");
		if (IS_ERR(poll_task)) {
			ret = PTR_ERR(poll_task);
			dev_err(charger->dev,
				"Unable to run kthread err %d\n", ret);
			return ret;
		}

		charger->poll_task = poll_task;
		return 0;
	}

	/* Create IRQ threads for charger interrupts */
	for (i = 0; i < NUM_CHARGER_IRQS; i++) {
		ret = devm_request_threaded_irq(&pdev->dev, irq[i], NULL,
						tps65217_charger_irq,
						0, "tps65217-charger",
						charger);
		if (ret) {
			dev_err(charger->dev,
				"Unable to register irq %d err %d\n", irq[i],
				ret);
			return ret;
		}

		/* Check current state */
		tps65217_charger_irq(-1, charger);
	}

	return 0;
}