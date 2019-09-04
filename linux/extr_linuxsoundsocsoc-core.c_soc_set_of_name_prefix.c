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
struct snd_soc_component {char const* name_prefix; TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; struct device_node* of_node; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int of_property_read_string (struct device_node*,char*,char const**) ; 

__attribute__((used)) static void soc_set_of_name_prefix(struct snd_soc_component *component)
{
	struct device_node *component_of_node = component->dev->of_node;
	const char *str;
	int ret;

	if (!component_of_node && component->dev->parent)
		component_of_node = component->dev->parent->of_node;

	ret = of_property_read_string(component_of_node, "sound-name-prefix",
				      &str);
	if (!ret)
		component->name_prefix = str;
}