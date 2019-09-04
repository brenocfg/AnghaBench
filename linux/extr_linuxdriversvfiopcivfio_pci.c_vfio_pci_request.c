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
struct vfio_pci_device {int /*<<< orphan*/  igate; TYPE_1__* pdev; scalar_t__ req_trigger; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_notice_ratelimited (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eventfd_signal (scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_pci_request(void *device_data, unsigned int count)
{
	struct vfio_pci_device *vdev = device_data;

	mutex_lock(&vdev->igate);

	if (vdev->req_trigger) {
		if (!(count % 10))
			dev_notice_ratelimited(&vdev->pdev->dev,
				"Relaying device request to user (#%u)\n",
				count);
		eventfd_signal(vdev->req_trigger, 1);
	} else if (count == 0) {
		dev_warn(&vdev->pdev->dev,
			"No device request channel registered, blocked until released by user\n");
	}

	mutex_unlock(&vdev->igate);
}