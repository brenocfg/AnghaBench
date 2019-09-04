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
struct drm_audio_component {TYPE_2__* ops; TYPE_1__* audio_ops; scalar_t__ dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int (* master_bind ) (struct device*,struct drm_audio_component*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int component_bind_all (struct device*,struct drm_audio_component*) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_audio_component*) ; 
 struct drm_audio_component* hdac_get_acomp (struct device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct device*,struct drm_audio_component*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdac_component_master_bind(struct device *dev)
{
	struct drm_audio_component *acomp = hdac_get_acomp(dev);
	int ret;

	if (WARN_ON(!acomp))
		return -EINVAL;

	ret = component_bind_all(dev, acomp);
	if (ret < 0)
		return ret;

	if (WARN_ON(!(acomp->dev && acomp->ops))) {
		ret = -EINVAL;
		goto out_unbind;
	}

	/* pin the module to avoid dynamic unbinding, but only if given */
	if (!try_module_get(acomp->ops->owner)) {
		ret = -ENODEV;
		goto out_unbind;
	}

	if (acomp->audio_ops && acomp->audio_ops->master_bind) {
		ret = acomp->audio_ops->master_bind(dev, acomp);
		if (ret < 0)
			goto module_put;
	}

	return 0;

 module_put:
	module_put(acomp->ops->owner);
out_unbind:
	component_unbind_all(dev, acomp);

	return ret;
}