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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int devm_request_irq (struct device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void*) ; 

__attribute__((used)) static int rspi_request_irq(struct device *dev, unsigned int irq,
			    irq_handler_t handler, const char *suffix,
			    void *dev_id)
{
	const char *name = devm_kasprintf(dev, GFP_KERNEL, "%s:%s",
					  dev_name(dev), suffix);
	if (!name)
		return -ENOMEM;

	return devm_request_irq(dev, irq, handler, 0, name, dev_id);
}