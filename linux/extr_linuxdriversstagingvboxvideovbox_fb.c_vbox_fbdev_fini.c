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
struct vbox_private {struct vbox_fbdev* fbdev; } ;
struct vbox_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/ * obj; } ;
struct vbox_fbdev {int /*<<< orphan*/  helper; struct vbox_framebuffer afb; } ;
struct TYPE_2__ {scalar_t__ virtual; } ;
struct vbox_bo {scalar_t__ pin_count; TYPE_1__ kmap; } ;
struct drm_device {struct vbox_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct vbox_bo* gem_to_vbox_bo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (TYPE_1__*) ; 
 int /*<<< orphan*/  vbox_bo_reserve (struct vbox_bo*,int) ; 
 int /*<<< orphan*/  vbox_bo_unpin (struct vbox_bo*) ; 
 int /*<<< orphan*/  vbox_bo_unreserve (struct vbox_bo*) ; 

void vbox_fbdev_fini(struct drm_device *dev)
{
	struct vbox_private *vbox = dev->dev_private;
	struct vbox_fbdev *fbdev = vbox->fbdev;
	struct vbox_framebuffer *afb = &fbdev->afb;

#ifdef CONFIG_DRM_KMS_FB_HELPER
	if (fbdev->helper.fbdev && fbdev->helper.fbdev->fbdefio)
		fb_deferred_io_cleanup(fbdev->helper.fbdev);
#endif

	drm_fb_helper_unregister_fbi(&fbdev->helper);

	if (afb->obj) {
		struct vbox_bo *bo = gem_to_vbox_bo(afb->obj);

		if (!vbox_bo_reserve(bo, false)) {
			if (bo->kmap.virtual)
				ttm_bo_kunmap(&bo->kmap);
			/*
			 * QXL does this, but is it really needed before
			 * freeing?
			 */
			if (bo->pin_count)
				vbox_bo_unpin(bo);
			vbox_bo_unreserve(bo);
		}
		drm_gem_object_put_unlocked(afb->obj);
		afb->obj = NULL;
	}
	drm_fb_helper_fini(&fbdev->helper);

	drm_framebuffer_unregister_private(&afb->base);
	drm_framebuffer_cleanup(&afb->base);
}