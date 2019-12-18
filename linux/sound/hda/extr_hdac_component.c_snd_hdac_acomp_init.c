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
struct hdac_bus {struct drm_audio_component* audio_component; struct device* dev; } ;
struct drm_audio_component_audio_ops {int dummy; } ;
struct drm_audio_component {struct drm_audio_component_audio_ops const* audio_ops; } ;
struct device {int dummy; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int component_master_add_with_match (struct device*,int /*<<< orphan*/ *,struct component_match*) ; 
 int /*<<< orphan*/  component_match_add_typed (struct device*,struct component_match**,int (*) (struct device*,int,void*),struct hdac_bus*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  devres_add (struct device*,struct drm_audio_component*) ; 
 struct drm_audio_component* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdac_acomp_release ; 
 int /*<<< orphan*/  hdac_component_master_ops ; 
 int /*<<< orphan*/  hdac_get_acomp (struct device*) ; 

int snd_hdac_acomp_init(struct hdac_bus *bus,
			const struct drm_audio_component_audio_ops *aops,
			int (*match_master)(struct device *, int, void *),
			size_t extra_size)
{
	struct component_match *match = NULL;
	struct device *dev = bus->dev;
	struct drm_audio_component *acomp;
	int ret;

	if (WARN_ON(hdac_get_acomp(dev)))
		return -EBUSY;

	acomp = devres_alloc(hdac_acomp_release, sizeof(*acomp) + extra_size,
			     GFP_KERNEL);
	if (!acomp)
		return -ENOMEM;
	acomp->audio_ops = aops;
	bus->audio_component = acomp;
	devres_add(dev, acomp);

	component_match_add_typed(dev, &match, match_master, bus);
	ret = component_master_add_with_match(dev, &hdac_component_master_ops,
					      match);
	if (ret < 0)
		goto out_err;

	return 0;

out_err:
	bus->audio_component = NULL;
	devres_destroy(dev, hdac_acomp_release, NULL, NULL);
	dev_info(dev, "failed to add audio component master (%d)\n", ret);

	return ret;
}