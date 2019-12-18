#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wcd9335_codec {int /*<<< orphan*/  if_regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int WCD9335_SLIM_NUM_PORT_REG ; 
 scalar_t__ WCD9335_SLIM_PGD_PORT_INT_EN0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wcd9335_codec*) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_1__* wcd9335_irqs ; 

__attribute__((used)) static int wcd9335_setup_irqs(struct wcd9335_codec *wcd)
{
	int irq, ret, i;

	for (i = 0; i < ARRAY_SIZE(wcd9335_irqs); i++) {
		irq = regmap_irq_get_virq(wcd->irq_data, wcd9335_irqs[i].irq);
		if (irq < 0) {
			dev_err(wcd->dev, "Failed to get %s\n",
					wcd9335_irqs[i].name);
			return irq;
		}

		ret = devm_request_threaded_irq(wcd->dev, irq, NULL,
						wcd9335_irqs[i].handler,
						IRQF_TRIGGER_RISING |
						IRQF_ONESHOT,
						wcd9335_irqs[i].name, wcd);
		if (ret) {
			dev_err(wcd->dev, "Failed to request %s\n",
					wcd9335_irqs[i].name);
			return ret;
		}
	}

	/* enable interrupts on all slave ports */
	for (i = 0; i < WCD9335_SLIM_NUM_PORT_REG; i++)
		regmap_write(wcd->if_regmap, WCD9335_SLIM_PGD_PORT_INT_EN0 + i,
			     0xFF);

	return ret;
}