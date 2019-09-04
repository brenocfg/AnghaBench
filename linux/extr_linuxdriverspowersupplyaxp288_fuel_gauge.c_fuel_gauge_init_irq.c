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
struct axp288_fg_info {int* irq; TYPE_1__* pdev; int /*<<< orphan*/  regmap_irqc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AXP288_FG_INTR_NUM ; 
 int /*<<< orphan*/  DEV_NAME ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  free_irq (int,struct axp288_fg_info*) ; 
 int /*<<< orphan*/  fuel_gauge_thread_handler ; 
 int platform_get_irq (TYPE_1__*,int) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct axp288_fg_info*) ; 

__attribute__((used)) static void fuel_gauge_init_irq(struct axp288_fg_info *info)
{
	int ret, i, pirq;

	for (i = 0; i < AXP288_FG_INTR_NUM; i++) {
		pirq = platform_get_irq(info->pdev, i);
		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		if (info->irq[i] < 0) {
			dev_warn(&info->pdev->dev,
				"regmap_irq get virq failed for IRQ %d: %d\n",
				pirq, info->irq[i]);
			info->irq[i] = -1;
			goto intr_failed;
		}
		ret = request_threaded_irq(info->irq[i],
				NULL, fuel_gauge_thread_handler,
				IRQF_ONESHOT, DEV_NAME, info);
		if (ret) {
			dev_warn(&info->pdev->dev,
				"request irq failed for IRQ %d: %d\n",
				pirq, info->irq[i]);
			info->irq[i] = -1;
			goto intr_failed;
		} else {
			dev_info(&info->pdev->dev, "HW IRQ %d -> VIRQ %d\n",
				pirq, info->irq[i]);
		}
	}
	return;

intr_failed:
	for (; i > 0; i--) {
		free_irq(info->irq[i - 1], info);
		info->irq[i - 1] = -1;
	}
}