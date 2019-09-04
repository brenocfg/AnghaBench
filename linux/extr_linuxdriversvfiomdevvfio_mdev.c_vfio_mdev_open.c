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
struct mdev_parent {TYPE_1__* ops; } ;
struct mdev_device {struct mdev_parent* parent; } ;
struct TYPE_2__ {int (* open ) (struct mdev_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct mdev_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vfio_mdev_open(void *device_data)
{
	struct mdev_device *mdev = device_data;
	struct mdev_parent *parent = mdev->parent;
	int ret;

	if (unlikely(!parent->ops->open))
		return -EINVAL;

	if (!try_module_get(THIS_MODULE))
		return -ENODEV;

	ret = parent->ops->open(mdev);
	if (ret)
		module_put(THIS_MODULE);

	return ret;
}