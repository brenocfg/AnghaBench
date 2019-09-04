#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct umc_dev {TYPE_1__ resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,TYPE_1__*,int) ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 
 int request_resource (int /*<<< orphan*/ ,TYPE_1__*) ; 

int umc_device_register(struct umc_dev *umc)
{
	int err;

	err = request_resource(umc->resource.parent, &umc->resource);
	if (err < 0) {
		dev_err(&umc->dev, "can't allocate resource range %pR: %d\n",
			&umc->resource, err);
		goto error_request_resource;
	}

	err = device_register(&umc->dev);
	if (err < 0)
		goto error_device_register;
	return 0;

error_device_register:
	put_device(&umc->dev);
	release_resource(&umc->resource);
error_request_resource:
	return err;
}