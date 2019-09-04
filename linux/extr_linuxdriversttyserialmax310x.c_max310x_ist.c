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
struct max310x_port {TYPE_1__* devtype; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int nr; } ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  MAX310X_GLOBALIRQ_REG ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ fls (unsigned int) ; 
 scalar_t__ max310x_port_irq (struct max310x_port*,scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t max310x_ist(int irq, void *dev_id)
{
	struct max310x_port *s = (struct max310x_port *)dev_id;
	bool handled = false;

	if (s->devtype->nr > 1) {
		do {
			unsigned int val = ~0;

			WARN_ON_ONCE(regmap_read(s->regmap,
						 MAX310X_GLOBALIRQ_REG, &val));
			val = ((1 << s->devtype->nr) - 1) & ~val;
			if (!val)
				break;
			if (max310x_port_irq(s, fls(val) - 1) == IRQ_HANDLED)
				handled = true;
		} while (1);
	} else {
		if (max310x_port_irq(s, 0) == IRQ_HANDLED)
			handled = true;
	}

	return IRQ_RETVAL(handled);
}