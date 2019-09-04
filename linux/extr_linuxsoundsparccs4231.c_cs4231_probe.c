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

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int cs4231_probe(struct platform_device *op)
{
#ifdef EBUS_SUPPORT
	if (!strcmp(op->dev.of_node->parent->name, "ebus"))
		return cs4231_ebus_probe(op);
#endif
#ifdef SBUS_SUPPORT
	if (!strcmp(op->dev.of_node->parent->name, "sbus") ||
	    !strcmp(op->dev.of_node->parent->name, "sbi"))
		return cs4231_sbus_probe(op);
#endif
	return -ENODEV;
}