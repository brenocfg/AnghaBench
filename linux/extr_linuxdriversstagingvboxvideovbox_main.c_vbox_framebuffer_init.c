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
struct vbox_framebuffer {int /*<<< orphan*/  base; struct drm_gem_object* obj; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;
struct DRM_MODE_FB_CMD {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int drm_framebuffer_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,int /*<<< orphan*/ *,struct DRM_MODE_FB_CMD const*) ; 
 int /*<<< orphan*/  vbox_fb_funcs ; 

int vbox_framebuffer_init(struct drm_device *dev,
			  struct vbox_framebuffer *vbox_fb,
			  const struct DRM_MODE_FB_CMD *mode_cmd,
			  struct drm_gem_object *obj)
{
	int ret;

	drm_helper_mode_fill_fb_struct(dev, &vbox_fb->base, mode_cmd);
	vbox_fb->obj = obj;
	ret = drm_framebuffer_init(dev, &vbox_fb->base, &vbox_fb_funcs);
	if (ret) {
		DRM_ERROR("framebuffer init failed %d\n", ret);
		return ret;
	}

	return 0;
}