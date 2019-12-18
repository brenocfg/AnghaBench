#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_audio_component {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  dev; struct drm_audio_component* audio_component; } ;
struct drm_audio_component {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MODULES ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_complete ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i915_component_master_match ; 
 int /*<<< orphan*/  i915_gfx_present () ; 
 int /*<<< orphan*/  i915_init_ops ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  snd_hdac_acomp_exit (struct hdac_bus*) ; 
 int snd_hdac_acomp_init (struct hdac_bus*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_hdac_i915_init(struct hdac_bus *bus)
{
	struct drm_audio_component *acomp;
	int err;

	if (!i915_gfx_present())
		return -ENODEV;

	init_completion(&bind_complete);

	err = snd_hdac_acomp_init(bus, &i915_init_ops,
				  i915_component_master_match,
				  sizeof(struct i915_audio_component) - sizeof(*acomp));
	if (err < 0)
		return err;
	acomp = bus->audio_component;
	if (!acomp)
		return -ENODEV;
	if (!acomp->ops) {
		if (!IS_ENABLED(CONFIG_MODULES) ||
		    !request_module("i915")) {
			/* 60s timeout */
			wait_for_completion_timeout(&bind_complete,
						   msecs_to_jiffies(60 * 1000));
		}
	}
	if (!acomp->ops) {
		dev_info(bus->dev, "couldn't bind with audio component\n");
		snd_hdac_acomp_exit(bus);
		return -ENODEV;
	}
	return 0;
}