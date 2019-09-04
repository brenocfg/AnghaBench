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
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_count_strings (struct device_node*,char*) ; 

__attribute__((used)) static const char *sunxi_pctrl_find_pins_prop(struct device_node *node,
					      int *npins)
{
	int count;

	/* Try the generic binding */
	count = of_property_count_strings(node, "pins");
	if (count > 0) {
		*npins = count;
		return "pins";
	}

	/* And fall back to our legacy one */
	count = of_property_count_strings(node, "allwinner,pins");
	if (count > 0) {
		*npins = count;
		return "allwinner,pins";
	}

	return NULL;
}