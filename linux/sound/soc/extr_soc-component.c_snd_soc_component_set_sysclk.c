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
struct TYPE_2__ {int (* set_sysclk ) (struct snd_soc_component*,int,int,unsigned int,int) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct snd_soc_component*,int,int,unsigned int,int) ; 

int snd_soc_component_set_sysclk(struct snd_soc_component *component,
				 int clk_id, int source, unsigned int freq,
				 int dir)
{
	if (component->driver->set_sysclk)
		return component->driver->set_sysclk(component, clk_id, source,
						     freq, dir);

	return -ENOTSUPP;
}