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
struct irq_devres {unsigned int irq; void* dev_id; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_irq_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct irq_devres*) ; 
 struct irq_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct irq_devres*) ; 
 int request_threaded_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,char const*,void*) ; 

int devm_request_threaded_irq(struct device *dev, unsigned int irq,
			      irq_handler_t handler, irq_handler_t thread_fn,
			      unsigned long irqflags, const char *devname,
			      void *dev_id)
{
	struct irq_devres *dr;
	int rc;

	dr = devres_alloc(devm_irq_release, sizeof(struct irq_devres),
			  GFP_KERNEL);
	if (!dr)
		return -ENOMEM;

	if (!devname)
		devname = dev_name(dev);

	rc = request_threaded_irq(irq, handler, thread_fn, irqflags, devname,
				  dev_id);
	if (rc) {
		devres_free(dr);
		return rc;
	}

	dr->irq = irq;
	dr->dev_id = dev_id;
	devres_add(dev, dr);

	return 0;
}