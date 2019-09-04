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
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; TYPE_1__* np; } ;
struct irq_fwspec {int param_count; int /*<<< orphan*/ * param; int /*<<< orphan*/ * fwnode; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */

__attribute__((used)) static void of_phandle_args_to_fwspec(struct of_phandle_args *irq_data,
				      struct irq_fwspec *fwspec)
{
	int i;

	fwspec->fwnode = irq_data->np ? &irq_data->np->fwnode : NULL;
	fwspec->param_count = irq_data->args_count;

	for (i = 0; i < irq_data->args_count; i++)
		fwspec->param[i] = irq_data->args[i];
}