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
struct vfio_platform_device {int /*<<< orphan*/  reset_required; int /*<<< orphan*/  parent_module; int /*<<< orphan*/  get_irq; int /*<<< orphan*/  get_resource; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; void* opaque; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VFIO_DEVICE_FLAGS_PLATFORM ; 
 int /*<<< orphan*/  get_platform_irq ; 
 int /*<<< orphan*/  get_platform_resource ; 
 int /*<<< orphan*/  kfree (struct vfio_platform_device*) ; 
 struct vfio_platform_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_required ; 
 int vfio_platform_probe_common (struct vfio_platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_platform_probe(struct platform_device *pdev)
{
	struct vfio_platform_device *vdev;
	int ret;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev)
		return -ENOMEM;

	vdev->opaque = (void *) pdev;
	vdev->name = pdev->name;
	vdev->flags = VFIO_DEVICE_FLAGS_PLATFORM;
	vdev->get_resource = get_platform_resource;
	vdev->get_irq = get_platform_irq;
	vdev->parent_module = THIS_MODULE;
	vdev->reset_required = reset_required;

	ret = vfio_platform_probe_common(vdev, &pdev->dev);
	if (ret)
		kfree(vdev);

	return ret;
}