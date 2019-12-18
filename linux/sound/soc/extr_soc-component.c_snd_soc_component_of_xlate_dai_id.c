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
struct snd_soc_component {TYPE_1__* driver; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int (* of_xlate_dai_id ) (struct snd_soc_component*,struct device_node*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct snd_soc_component*,struct device_node*) ; 

int snd_soc_component_of_xlate_dai_id(struct snd_soc_component *component,
				      struct device_node *ep)
{
	if (component->driver->of_xlate_dai_id)
		return component->driver->of_xlate_dai_id(component, ep);

	return -ENOTSUPP;
}