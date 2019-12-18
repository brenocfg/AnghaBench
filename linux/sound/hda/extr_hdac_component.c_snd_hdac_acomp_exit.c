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
struct hdac_bus {struct drm_audio_component* audio_component; scalar_t__ display_power_status; int /*<<< orphan*/  display_power_active; struct device* dev; } ;
struct drm_audio_component {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put_power ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_master_del (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdac_acomp_release ; 
 int /*<<< orphan*/  hdac_component_master_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_hdac_acomp_exit(struct hdac_bus *bus)
{
	struct device *dev = bus->dev;
	struct drm_audio_component *acomp = bus->audio_component;

	if (!acomp)
		return 0;

	if (WARN_ON(bus->display_power_active) && acomp->ops)
		acomp->ops->put_power(acomp->dev, bus->display_power_active);

	bus->display_power_active = 0;
	bus->display_power_status = 0;

	component_master_del(dev, &hdac_component_master_ops);

	bus->audio_component = NULL;
	devres_destroy(dev, hdac_acomp_release, NULL, NULL);

	return 0;
}