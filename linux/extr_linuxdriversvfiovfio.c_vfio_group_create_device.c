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
struct vfio_group {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  device_list; } ;
struct vfio_device_ops {int dummy; } ;
struct vfio_device {int /*<<< orphan*/  group_next; void* device_data; struct vfio_device_ops const* ops; struct vfio_group* group; struct device* dev; int /*<<< orphan*/  kref; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vfio_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct vfio_device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct vfio_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_group_get (struct vfio_group*) ; 

__attribute__((used)) static
struct vfio_device *vfio_group_create_device(struct vfio_group *group,
					     struct device *dev,
					     const struct vfio_device_ops *ops,
					     void *device_data)
{
	struct vfio_device *device;

	device = kzalloc(sizeof(*device), GFP_KERNEL);
	if (!device)
		return ERR_PTR(-ENOMEM);

	kref_init(&device->kref);
	device->dev = dev;
	device->group = group;
	device->ops = ops;
	device->device_data = device_data;
	dev_set_drvdata(dev, device);

	/* No need to get group_lock, caller has group reference */
	vfio_group_get(group);

	mutex_lock(&group->device_lock);
	list_add(&device->group_next, &group->device_list);
	mutex_unlock(&group->device_lock);

	return device;
}