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
struct tape_request {int /*<<< orphan*/  status; int /*<<< orphan*/  options; int /*<<< orphan*/  cpaddr; } ;
struct tape_device {int /*<<< orphan*/  tape_dnr; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  TAPE_REQUEST_IN_IO ; 
 int /*<<< orphan*/  TAPE_REQUEST_QUEUED ; 
 int ccw_device_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__tape_start_io(struct tape_device *device, struct tape_request *request)
{
	int rc;

	rc = ccw_device_start(
		device->cdev,
		request->cpaddr,
		(unsigned long) request,
		0x00,
		request->options
	);
	if (rc == 0) {
		request->status = TAPE_REQUEST_IN_IO;
	} else if (rc == -EBUSY) {
		/* The common I/O subsystem is currently busy. Retry later. */
		request->status = TAPE_REQUEST_QUEUED;
		schedule_delayed_work(&device->tape_dnr, 0);
		rc = 0;
	} else {
		/* Start failed. Remove request and indicate failure. */
		DBF_EVENT(1, "tape: start request failed with RC = %i\n", rc);
	}
	return rc;
}