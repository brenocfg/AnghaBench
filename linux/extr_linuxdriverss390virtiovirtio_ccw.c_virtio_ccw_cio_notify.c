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
struct virtio_ccw_device {int device_lost; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CIO_GONE 129 
#define  CIO_OPER 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 struct virtio_ccw_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtio_ccw_cio_notify(struct ccw_device *cdev, int event)
{
	int rc;
	struct virtio_ccw_device *vcdev = dev_get_drvdata(&cdev->dev);

	/*
	 * Make sure vcdev is set
	 * i.e. set_offline/remove callback not already running
	 */
	if (!vcdev)
		return NOTIFY_DONE;

	switch (event) {
	case CIO_GONE:
		vcdev->device_lost = true;
		rc = NOTIFY_DONE;
		break;
	case CIO_OPER:
		rc = NOTIFY_OK;
		break;
	default:
		rc = NOTIFY_DONE;
		break;
	}
	return rc;
}