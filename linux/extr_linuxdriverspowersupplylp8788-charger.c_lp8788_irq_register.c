#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lp8788_charger {scalar_t__ num_irqs; int /*<<< orphan*/  charger_work; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* LP8788_BATT_IRQ ; 
 char const* LP8788_CHG_IRQ ; 
 scalar_t__ LP8788_MAX_CHG_IRQS ; 
 char const* LP8788_PRSW_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lp8788_charger_event ; 
 int lp8788_set_irqs (struct platform_device*,struct lp8788_charger*,char const*) ; 

__attribute__((used)) static int lp8788_irq_register(struct platform_device *pdev,
				struct lp8788_charger *pchg)
{
	const char *name[] = {
		LP8788_CHG_IRQ, LP8788_PRSW_IRQ, LP8788_BATT_IRQ
	};
	int i;
	int ret;

	INIT_WORK(&pchg->charger_work, lp8788_charger_event);
	pchg->num_irqs = 0;

	for (i = 0; i < ARRAY_SIZE(name); i++) {
		ret = lp8788_set_irqs(pdev, pchg, name[i]);
		if (ret) {
			dev_warn(&pdev->dev, "irq setup failed: %s\n", name[i]);
			return ret;
		}
	}

	if (pchg->num_irqs > LP8788_MAX_CHG_IRQS) {
		dev_err(&pdev->dev, "invalid total number of irqs: %d\n",
			pchg->num_irqs);
		return -EINVAL;
	}


	return 0;
}