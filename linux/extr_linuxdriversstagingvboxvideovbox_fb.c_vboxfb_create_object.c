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
typedef  int u32 ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct vbox_fbdev {TYPE_1__ helper; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;
struct DRM_MODE_FB_CMD {int* pitches; int height; } ;

/* Variables and functions */
 int vbox_gem_create (struct drm_device*,int,int,struct drm_gem_object**) ; 

__attribute__((used)) static int vboxfb_create_object(struct vbox_fbdev *fbdev,
				struct DRM_MODE_FB_CMD *mode_cmd,
				struct drm_gem_object **gobj_p)
{
	struct drm_device *dev = fbdev->helper.dev;
	u32 size;
	struct drm_gem_object *gobj;
	u32 pitch = mode_cmd->pitches[0];
	int ret;

	size = pitch * mode_cmd->height;
	ret = vbox_gem_create(dev, size, true, &gobj);
	if (ret)
		return ret;

	*gobj_p = gobj;

	return 0;
}