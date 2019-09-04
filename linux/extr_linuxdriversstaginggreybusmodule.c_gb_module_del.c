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
struct gb_module {size_t num_interfaces; int /*<<< orphan*/  dev; int /*<<< orphan*/ * interfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_module_deregister_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_module_del (struct gb_module*) ; 

void gb_module_del(struct gb_module *module)
{
	size_t i;

	for (i = 0; i < module->num_interfaces; ++i)
		gb_module_deregister_interface(module->interfaces[i]);

	trace_gb_module_del(module);

	device_del(&module->dev);
}