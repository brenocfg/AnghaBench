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
struct irqaction {unsigned long flags; char const* name; void* dev_id; scalar_t__ handler; } ;
struct irq_desc {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  lock; int /*<<< orphan*/  istate; } ;
typedef  scalar_t__ irq_handler_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IRQF_COND_SUSPEND ; 
 unsigned long IRQF_IRQPOLL ; 
 unsigned long IRQF_NOBALANCING ; 
 unsigned long IRQF_NO_THREAD ; 
 unsigned long IRQF_PERCPU ; 
 unsigned long IRQF_SHARED ; 
 int /*<<< orphan*/  IRQS_NMI ; 
 unsigned int IRQ_NOTCONNECTED ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cleanup_nmi (unsigned int,struct irq_desc*) ; 
 int __setup_irq (unsigned int,struct irq_desc*,struct irqaction*) ; 
 int irq_chip_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_chip_pm_put (int /*<<< orphan*/ *) ; 
 int irq_nmi_setup (struct irq_desc*) ; 
 scalar_t__ irq_settings_can_autoenable (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_settings_can_request (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_settings_is_per_cpu_devid (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_supports_nmi (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct irqaction*) ; 
 struct irqaction* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int request_nmi(unsigned int irq, irq_handler_t handler,
		unsigned long irqflags, const char *name, void *dev_id)
{
	struct irqaction *action;
	struct irq_desc *desc;
	unsigned long flags;
	int retval;

	if (irq == IRQ_NOTCONNECTED)
		return -ENOTCONN;

	/* NMI cannot be shared, used for Polling */
	if (irqflags & (IRQF_SHARED | IRQF_COND_SUSPEND | IRQF_IRQPOLL))
		return -EINVAL;

	if (!(irqflags & IRQF_PERCPU))
		return -EINVAL;

	if (!handler)
		return -EINVAL;

	desc = irq_to_desc(irq);

	if (!desc || irq_settings_can_autoenable(desc) ||
	    !irq_settings_can_request(desc) ||
	    WARN_ON(irq_settings_is_per_cpu_devid(desc)) ||
	    !irq_supports_nmi(desc))
		return -EINVAL;

	action = kzalloc(sizeof(struct irqaction), GFP_KERNEL);
	if (!action)
		return -ENOMEM;

	action->handler = handler;
	action->flags = irqflags | IRQF_NO_THREAD | IRQF_NOBALANCING;
	action->name = name;
	action->dev_id = dev_id;

	retval = irq_chip_pm_get(&desc->irq_data);
	if (retval < 0)
		goto err_out;

	retval = __setup_irq(irq, desc, action);
	if (retval)
		goto err_irq_setup;

	raw_spin_lock_irqsave(&desc->lock, flags);

	/* Setup NMI state */
	desc->istate |= IRQS_NMI;
	retval = irq_nmi_setup(desc);
	if (retval) {
		__cleanup_nmi(irq, desc);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
		return -EINVAL;
	}

	raw_spin_unlock_irqrestore(&desc->lock, flags);

	return 0;

err_irq_setup:
	irq_chip_pm_put(&desc->irq_data);
err_out:
	kfree(action);

	return retval;
}