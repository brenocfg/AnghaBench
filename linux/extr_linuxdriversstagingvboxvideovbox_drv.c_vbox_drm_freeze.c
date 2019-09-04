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
struct drm_device {int /*<<< orphan*/  pdev; struct vbox_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_set_suspend_unlocked (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vbox_drm_freeze(struct drm_device *dev)
{
	struct vbox_private *vbox = dev->dev_private;

	drm_kms_helper_poll_disable(dev);

	pci_save_state(dev->pdev);

	drm_fb_helper_set_suspend_unlocked(&vbox->fbdev->helper, true);

	return 0;
}