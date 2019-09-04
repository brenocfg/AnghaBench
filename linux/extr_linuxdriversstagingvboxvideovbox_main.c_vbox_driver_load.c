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
struct vbox_private {int /*<<< orphan*/  hw_mutex; struct drm_device* dev; } ;
struct TYPE_2__ {int min_width; int min_height; int preferred_depth; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; void* funcs; } ;
struct drm_device {TYPE_1__ mode_config; struct vbox_private* dev_private; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VBE_DISPI_ID_HGSMI ; 
 int /*<<< orphan*/  VBE_DISPI_MAX_XRES ; 
 int /*<<< orphan*/  VBE_DISPI_MAX_YRES ; 
 struct vbox_private* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbox_check_supported (int /*<<< orphan*/ ) ; 
 int vbox_fbdev_init (struct drm_device*) ; 
 int /*<<< orphan*/  vbox_hw_fini (struct vbox_private*) ; 
 int vbox_hw_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_irq_fini (struct vbox_private*) ; 
 int vbox_irq_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mm_fini (struct vbox_private*) ; 
 int vbox_mm_init (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_mode_fini (struct drm_device*) ; 
 int /*<<< orphan*/  vbox_mode_funcs ; 
 int vbox_mode_init (struct drm_device*) ; 

int vbox_driver_load(struct drm_device *dev)
{
	struct vbox_private *vbox;
	int ret = 0;

	if (!vbox_check_supported(VBE_DISPI_ID_HGSMI))
		return -ENODEV;

	vbox = devm_kzalloc(dev->dev, sizeof(*vbox), GFP_KERNEL);
	if (!vbox)
		return -ENOMEM;

	dev->dev_private = vbox;
	vbox->dev = dev;

	mutex_init(&vbox->hw_mutex);

	ret = vbox_hw_init(vbox);
	if (ret)
		return ret;

	ret = vbox_mm_init(vbox);
	if (ret)
		goto err_hw_fini;

	drm_mode_config_init(dev);

	dev->mode_config.funcs = (void *)&vbox_mode_funcs;
	dev->mode_config.min_width = 64;
	dev->mode_config.min_height = 64;
	dev->mode_config.preferred_depth = 24;
	dev->mode_config.max_width = VBE_DISPI_MAX_XRES;
	dev->mode_config.max_height = VBE_DISPI_MAX_YRES;

	ret = vbox_mode_init(dev);
	if (ret)
		goto err_drm_mode_cleanup;

	ret = vbox_irq_init(vbox);
	if (ret)
		goto err_mode_fini;

	ret = vbox_fbdev_init(dev);
	if (ret)
		goto err_irq_fini;

	return 0;

err_irq_fini:
	vbox_irq_fini(vbox);
err_mode_fini:
	vbox_mode_fini(dev);
err_drm_mode_cleanup:
	drm_mode_config_cleanup(dev);
	vbox_mm_fini(vbox);
err_hw_fini:
	vbox_hw_fini(vbox);
	return ret;
}