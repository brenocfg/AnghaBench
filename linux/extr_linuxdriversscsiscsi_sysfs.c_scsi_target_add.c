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
struct scsi_target {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ STARGET_CREATED ; 
 scalar_t__ STARGET_RUNNING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_enable_async_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_add_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scsi_target_add(struct scsi_target *starget)
{
	int error;

	if (starget->state != STARGET_CREATED)
		return 0;

	error = device_add(&starget->dev);
	if (error) {
		dev_err(&starget->dev, "target device_add failed, error %d\n", error);
		return error;
	}
	transport_add_device(&starget->dev);
	starget->state = STARGET_RUNNING;

	pm_runtime_set_active(&starget->dev);
	pm_runtime_enable(&starget->dev);
	device_enable_async_suspend(&starget->dev);

	return 0;
}