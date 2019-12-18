#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENODEV ; 
 int cs4231_ebus_probe (struct platform_device*) ; 
 int cs4231_sbus_probe (struct platform_device*) ; 
 scalar_t__ of_node_name_eq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cs4231_probe(struct platform_device *op)
{
#ifdef EBUS_SUPPORT
	if (of_node_name_eq(op->dev.of_node->parent, "ebus"))
		return cs4231_ebus_probe(op);
#endif
#ifdef SBUS_SUPPORT
	if (of_node_name_eq(op->dev.of_node->parent, "sbus") ||
	    of_node_name_eq(op->dev.of_node->parent, "sbi"))
		return cs4231_sbus_probe(op);
#endif
	return -ENODEV;
}