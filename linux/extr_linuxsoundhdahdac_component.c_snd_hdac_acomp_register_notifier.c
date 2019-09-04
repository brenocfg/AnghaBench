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
struct hdac_bus {TYPE_1__* audio_component; } ;
struct drm_audio_component_audio_ops {int dummy; } ;
struct TYPE_2__ {struct drm_audio_component_audio_ops const* audio_ops; } ;

/* Variables and functions */
 int ENODEV ; 

int snd_hdac_acomp_register_notifier(struct hdac_bus *bus,
				    const struct drm_audio_component_audio_ops *aops)
{
	if (!bus->audio_component)
		return -ENODEV;

	bus->audio_component->audio_ops = aops;
	return 0;
}