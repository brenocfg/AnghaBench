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
typedef  int /*<<< orphan*/  u32 ;
struct irq_fwspec {unsigned int param_count; int /*<<< orphan*/ * param; int /*<<< orphan*/ * fwnode; } ;
struct device_node {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */

__attribute__((used)) static void of_phandle_args_to_fwspec(struct device_node *np, const u32 *args,
				      unsigned int count,
				      struct irq_fwspec *fwspec)
{
	int i;

	fwspec->fwnode = np ? &np->fwnode : NULL;
	fwspec->param_count = count;

	for (i = 0; i < count; i++)
		fwspec->param[i] = args[i];
}