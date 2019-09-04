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
struct platform_device {int dummy; } ;
struct cpcap_interrupt_desc {char const* name; int irq; int /*<<< orphan*/  node; int /*<<< orphan*/  action; } ;
struct cpcap_battery_ddata {int /*<<< orphan*/  irq_list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_BATTERY_IRQ_ACTION_BATTERY_LOW ; 
 int /*<<< orphan*/  CPCAP_BATTERY_IRQ_ACTION_POWEROFF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  cpcap_battery_irq_thread ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 struct cpcap_interrupt_desc* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct cpcap_battery_ddata*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int cpcap_battery_init_irq(struct platform_device *pdev,
				  struct cpcap_battery_ddata *ddata,
				  const char *name)
{
	struct cpcap_interrupt_desc *d;
	int irq, error;

	irq = platform_get_irq_byname(pdev, name);
	if (irq < 0)
		return irq;

	error = devm_request_threaded_irq(ddata->dev, irq, NULL,
					  cpcap_battery_irq_thread,
					  IRQF_SHARED,
					  name, ddata);
	if (error) {
		dev_err(ddata->dev, "could not get irq %s: %i\n",
			name, error);

		return error;
	}

	d = devm_kzalloc(ddata->dev, sizeof(*d), GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	d->name = name;
	d->irq = irq;

	if (!strncmp(name, "lowbph", 6))
		d->action = CPCAP_BATTERY_IRQ_ACTION_BATTERY_LOW;
	else if (!strncmp(name, "lowbpl", 6))
		d->action = CPCAP_BATTERY_IRQ_ACTION_POWEROFF;

	list_add(&d->node, &ddata->irq_list);

	return 0;
}