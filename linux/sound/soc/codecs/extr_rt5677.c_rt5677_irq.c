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
struct rt5677_priv {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  domain; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int status_mask; int polarity_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RT5677_IRQ_CTRL1 ; 
 int RT5677_IRQ_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  handle_nested_irq (int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* rt5677_irq_descs ; 

__attribute__((used)) static irqreturn_t rt5677_irq(int unused, void *data)
{
	struct rt5677_priv *rt5677 = data;
	int ret = 0, loop, i, reg_irq, virq;
	bool irq_fired = false;

	mutex_lock(&rt5677->irq_lock);

	/*
	 * Loop to handle interrupts until the last i2c read shows no pending
	 * irqs. The interrupt line is shared by multiple interrupt sources.
	 * After the regmap_read() below, a new interrupt source line may
	 * become high before the regmap_write() finishes, so there isn't a
	 * rising edge on the shared interrupt line for the new interrupt. Thus,
	 * the loop is needed to avoid missing irqs.
	 *
	 * A safeguard of 20 loops is used to avoid hanging in the irq handler
	 * if there is something wrong with the interrupt status update. The
	 * interrupt sources here are audio jack plug/unplug events which
	 * shouldn't happen at a high frequency for a long period of time.
	 * Empirically, more than 3 loops have never been seen.
	 */
	for (loop = 0; loop < 20; loop++) {
		/* Read interrupt status */
		ret = regmap_read(rt5677->regmap, RT5677_IRQ_CTRL1, &reg_irq);
		if (ret) {
			dev_err(rt5677->dev, "failed reading IRQ status: %d\n",
				ret);
			goto exit;
		}

		irq_fired = false;
		for (i = 0; i < RT5677_IRQ_NUM; i++) {
			if (reg_irq & rt5677_irq_descs[i].status_mask) {
				irq_fired = true;
				virq = irq_find_mapping(rt5677->domain, i);
				if (virq)
					handle_nested_irq(virq);

				/* Clear the interrupt by flipping the polarity
				 * of the interrupt source line that fired
				 */
				reg_irq ^= rt5677_irq_descs[i].polarity_mask;
			}
		}
		if (!irq_fired)
			goto exit;

		ret = regmap_write(rt5677->regmap, RT5677_IRQ_CTRL1, reg_irq);
		if (ret) {
			dev_err(rt5677->dev, "failed updating IRQ status: %d\n",
				ret);
			goto exit;
		}
	}
exit:
	mutex_unlock(&rt5677->irq_lock);
	if (irq_fired)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}