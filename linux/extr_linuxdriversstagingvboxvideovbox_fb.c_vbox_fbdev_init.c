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
struct vbox_private {int /*<<< orphan*/  num_crtcs; struct vbox_fbdev* fbdev; } ;
struct vbox_fbdev {int /*<<< orphan*/  helper; int /*<<< orphan*/  dirty_lock; } ;
struct drm_device {int /*<<< orphan*/  dev; struct vbox_private* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vbox_fbdev* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int drm_fb_helper_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbox_fb_helper_funcs ; 

int vbox_fbdev_init(struct drm_device *dev)
{
	struct vbox_private *vbox = dev->dev_private;
	struct vbox_fbdev *fbdev;
	int ret;

	fbdev = devm_kzalloc(dev->dev, sizeof(*fbdev), GFP_KERNEL);
	if (!fbdev)
		return -ENOMEM;

	vbox->fbdev = fbdev;
	spin_lock_init(&fbdev->dirty_lock);

	drm_fb_helper_prepare(dev, &fbdev->helper, &vbox_fb_helper_funcs);
	ret = drm_fb_helper_init(dev, &fbdev->helper, vbox->num_crtcs);
	if (ret)
		return ret;

	ret = drm_fb_helper_single_add_all_connectors(&fbdev->helper);
	if (ret)
		goto err_fini;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(&fbdev->helper, 32);
	if (ret)
		goto err_fini;

	return 0;

err_fini:
	drm_fb_helper_fini(&fbdev->helper);
	return ret;
}