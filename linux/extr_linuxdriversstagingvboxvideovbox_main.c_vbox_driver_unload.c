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
struct vbox_private {int dummy; } ;
struct drm_device {struct vbox_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  vbox_fbdev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  vbox_hw_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_irq_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mm_fini (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mode_fini (struct drm_device*) ; 

void vbox_driver_unload(struct drm_device *dev)
{
	struct vbox_private *vbox = dev->dev_private;

	vbox_fbdev_fini(dev);
	vbox_irq_fini(vbox);
	vbox_mode_fini(dev);
	drm_mode_config_cleanup(dev);
	vbox_mm_fini(vbox);
	vbox_hw_fini(vbox);
}