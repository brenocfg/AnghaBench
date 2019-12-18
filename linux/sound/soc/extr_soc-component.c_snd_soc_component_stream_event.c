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
struct TYPE_2__ {int (* stream_event ) (struct snd_soc_component*,int) ;} ;

/* Variables and functions */
 int stub1 (struct snd_soc_component*,int) ; 

int snd_soc_component_stream_event(struct snd_soc_component *component,
				   int event)
{
	if (component->driver->stream_event)
		return component->driver->stream_event(component, event);

	return 0;
}