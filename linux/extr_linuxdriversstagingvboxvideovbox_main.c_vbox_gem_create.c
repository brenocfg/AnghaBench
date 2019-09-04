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
typedef  scalar_t__ u32 ;
struct drm_gem_object {int dummy; } ;
struct vbox_bo {struct drm_gem_object gem; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 int vbox_bo_create (struct drm_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vbox_bo**) ; 

int vbox_gem_create(struct drm_device *dev,
		    u32 size, bool iskernel, struct drm_gem_object **obj)
{
	struct vbox_bo *vboxbo;
	int ret;

	*obj = NULL;

	size = roundup(size, PAGE_SIZE);
	if (size == 0)
		return -EINVAL;

	ret = vbox_bo_create(dev, size, 0, 0, &vboxbo);
	if (ret) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("failed to allocate GEM object\n");
		return ret;
	}

	*obj = &vboxbo->gem;

	return 0;
}