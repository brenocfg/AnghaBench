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
struct snd_soc_component {TYPE_2__* driver; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* open ) (struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 int stub1 (struct snd_pcm_substream*) ; 

int snd_soc_component_open(struct snd_soc_component *component,
			   struct snd_pcm_substream *substream)
{
	if (component->driver->ops &&
	    component->driver->ops->open)
		return component->driver->ops->open(substream);

	return 0;
}