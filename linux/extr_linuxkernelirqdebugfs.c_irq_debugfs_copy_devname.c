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
struct irq_desc {int /*<<< orphan*/  dev_name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* dev_name (struct device*) ; 
 struct irq_desc* irq_to_desc (int) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 

void irq_debugfs_copy_devname(int irq, struct device *dev)
{
	struct irq_desc *desc = irq_to_desc(irq);
	const char *name = dev_name(dev);

	if (name)
		desc->dev_name = kstrdup(name, GFP_KERNEL);
}