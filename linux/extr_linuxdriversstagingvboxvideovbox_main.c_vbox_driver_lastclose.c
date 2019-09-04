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
 int /*<<< orphan*/  drm_fb_helper_restore_fbdev_mode_unlocked (int /*<<< orphan*/ *) ; 

void vbox_driver_lastclose(struct drm_device *dev)
{
	struct vbox_private *vbox = dev->dev_private;

	if (vbox->fbdev)
		drm_fb_helper_restore_fbdev_mode_unlocked(&vbox->fbdev->helper);
}