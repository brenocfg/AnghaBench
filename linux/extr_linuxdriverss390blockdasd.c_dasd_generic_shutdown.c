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
struct dasd_device {scalar_t__ block; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  _wait_for_empty_queues (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (scalar_t__) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  shutdown_waitq ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dasd_generic_shutdown(struct ccw_device *cdev)
{
	struct dasd_device *device;

	device = dasd_device_from_cdev(cdev);
	if (IS_ERR(device))
		return;

	if (device->block)
		dasd_schedule_block_bh(device->block);

	dasd_schedule_device_bh(device);

	wait_event(shutdown_waitq, _wait_for_empty_queues(device));
}