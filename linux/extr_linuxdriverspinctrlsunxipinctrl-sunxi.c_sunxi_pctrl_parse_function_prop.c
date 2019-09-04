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
 int of_property_read_string (struct device_node*,char*,char const**) ; 

__attribute__((used)) static const char *sunxi_pctrl_parse_function_prop(struct device_node *node)
{
	const char *function;
	int ret;

	/* Try the generic binding */
	ret = of_property_read_string(node, "function", &function);
	if (!ret)
		return function;

	/* And fall back to our legacy one */
	ret = of_property_read_string(node, "allwinner,function", &function);
	if (!ret)
		return function;

	return NULL;
}