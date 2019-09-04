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
struct uio_listener {int /*<<< orphan*/  event_count; struct uio_device* dev; } ;
struct uio_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  info_lock; TYPE_1__* info; int /*<<< orphan*/  event; } ;
struct inode {int dummy; } ;
struct file {struct uio_listener* private_data; } ;
struct TYPE_2__ {int (* open ) (TYPE_1__*,struct inode*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 struct uio_device* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct uio_listener*) ; 
 struct uio_listener* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor_lock ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_idr ; 

__attribute__((used)) static int uio_open(struct inode *inode, struct file *filep)
{
	struct uio_device *idev;
	struct uio_listener *listener;
	int ret = 0;

	mutex_lock(&minor_lock);
	idev = idr_find(&uio_idr, iminor(inode));
	mutex_unlock(&minor_lock);
	if (!idev) {
		ret = -ENODEV;
		goto out;
	}

	get_device(&idev->dev);

	if (!try_module_get(idev->owner)) {
		ret = -ENODEV;
		goto err_module_get;
	}

	listener = kmalloc(sizeof(*listener), GFP_KERNEL);
	if (!listener) {
		ret = -ENOMEM;
		goto err_alloc_listener;
	}

	listener->dev = idev;
	listener->event_count = atomic_read(&idev->event);
	filep->private_data = listener;

	mutex_lock(&idev->info_lock);
	if (!idev->info) {
		mutex_unlock(&idev->info_lock);
		ret = -EINVAL;
		goto err_alloc_listener;
	}

	if (idev->info && idev->info->open)
		ret = idev->info->open(idev->info, inode);
	mutex_unlock(&idev->info_lock);
	if (ret)
		goto err_infoopen;

	return 0;

err_infoopen:
	kfree(listener);

err_alloc_listener:
	module_put(idev->owner);

err_module_get:
	put_device(&idev->dev);

out:
	return ret;
}