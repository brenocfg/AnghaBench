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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* set_jack ) (struct snd_soc_component*,struct snd_soc_jack*,void*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct snd_soc_component*,struct snd_soc_jack*,void*) ; 

int snd_soc_component_set_jack(struct snd_soc_component *component,
			       struct snd_soc_jack *jack, void *data)
{
	if (component->driver->set_jack)
		return component->driver->set_jack(component, jack, data);

	return -ENOTSUPP;
}