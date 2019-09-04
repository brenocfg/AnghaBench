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
struct ccw_device {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_schedule (int /*<<< orphan*/ ,struct ccw_device*) ; 
 int /*<<< orphan*/  virtio_ccw_auto_online ; 
 scalar_t__ virtio_ccw_check_autoonline (struct ccw_device*) ; 
 int /*<<< orphan*/  virtio_ccw_int_handler ; 

__attribute__((used)) static int virtio_ccw_probe(struct ccw_device *cdev)
{
	cdev->handler = virtio_ccw_int_handler;

	if (virtio_ccw_check_autoonline(cdev))
		async_schedule(virtio_ccw_auto_online, cdev);
	return 0;
}