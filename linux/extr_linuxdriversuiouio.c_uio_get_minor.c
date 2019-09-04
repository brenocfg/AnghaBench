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
struct uio_device {int minor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UIO_MAX_DEVICES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct uio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_idr ; 

__attribute__((used)) static int uio_get_minor(struct uio_device *idev)
{
	int retval = -ENOMEM;

	mutex_lock(&minor_lock);
	retval = idr_alloc(&uio_idr, idev, 0, UIO_MAX_DEVICES, GFP_KERNEL);
	if (retval >= 0) {
		idev->minor = retval;
		retval = 0;
	} else if (retval == -ENOSPC) {
		dev_err(&idev->dev, "too many uio devices\n");
		retval = -EINVAL;
	}
	mutex_unlock(&minor_lock);
	return retval;
}