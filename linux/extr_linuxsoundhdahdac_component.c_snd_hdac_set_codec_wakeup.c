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
struct hdac_bus {int /*<<< orphan*/  dev; struct drm_audio_component* audio_component; } ;
struct drm_audio_component {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* codec_wake_override ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

int snd_hdac_set_codec_wakeup(struct hdac_bus *bus, bool enable)
{
	struct drm_audio_component *acomp = bus->audio_component;

	if (!acomp || !acomp->ops)
		return -ENODEV;

	if (!acomp->ops->codec_wake_override)
		return 0;

	dev_dbg(bus->dev, "%s codec wakeup\n",
		enable ? "enable" : "disable");

	acomp->ops->codec_wake_override(acomp->dev, enable);

	return 0;
}