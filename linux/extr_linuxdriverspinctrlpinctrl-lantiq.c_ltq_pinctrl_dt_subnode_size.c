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

__attribute__((used)) static int ltq_pinctrl_dt_subnode_size(struct device_node *np)
{
	int ret;

	ret = of_property_count_strings(np, "lantiq,groups");
	if (ret < 0)
		ret = of_property_count_strings(np, "lantiq,pins");
	return ret;
}