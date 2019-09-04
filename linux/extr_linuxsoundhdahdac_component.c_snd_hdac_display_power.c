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
struct hdac_bus {int /*<<< orphan*/  drm_power_refcount; int /*<<< orphan*/  dev; struct drm_audio_component* audio_component; } ;
struct drm_audio_component {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put_power ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_power ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snd_hdac_set_codec_wakeup (struct hdac_bus*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int snd_hdac_display_power(struct hdac_bus *bus, bool enable)
{
	struct drm_audio_component *acomp = bus->audio_component;

	if (!acomp || !acomp->ops)
		return -ENODEV;

	dev_dbg(bus->dev, "display power %s\n",
		enable ? "enable" : "disable");

	if (enable) {
		if (!bus->drm_power_refcount++) {
			if (acomp->ops->get_power)
				acomp->ops->get_power(acomp->dev);
			snd_hdac_set_codec_wakeup(bus, true);
			snd_hdac_set_codec_wakeup(bus, false);
		}
	} else {
		WARN_ON(!bus->drm_power_refcount);
		if (!--bus->drm_power_refcount)
			if (acomp->ops->put_power)
				acomp->ops->put_power(acomp->dev);
	}

	return 0;
}