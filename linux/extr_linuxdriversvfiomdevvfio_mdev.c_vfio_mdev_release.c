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
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct mdev_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (struct mdev_device*)) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mdev_device*) ; 

__attribute__((used)) static void vfio_mdev_release(void *device_data)
{
	struct mdev_device *mdev = device_data;
	struct mdev_parent *parent = mdev->parent;

	if (likely(parent->ops->release))
		parent->ops->release(mdev);

	module_put(THIS_MODULE);
}