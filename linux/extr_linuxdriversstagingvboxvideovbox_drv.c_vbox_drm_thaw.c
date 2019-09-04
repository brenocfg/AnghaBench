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
struct vbox_private {TYPE_1__* fbdev; } ;
struct drm_device {struct vbox_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_set_suspend_unlocked (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_helper_resume_force_mode (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 

__attribute__((used)) static int vbox_drm_thaw(struct drm_device *dev)
{
	struct vbox_private *vbox = dev->dev_private;

	drm_mode_config_reset(dev);
	drm_helper_resume_force_mode(dev);
	drm_fb_helper_set_suspend_unlocked(&vbox->fbdev->helper, false);

	return 0;
}