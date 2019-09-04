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
struct scsi_device {scalar_t__ queue_depth; int /*<<< orphan*/  device_blocked; int /*<<< orphan*/  device_busy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool scsi_device_is_busy(struct scsi_device *sdev)
{
	if (atomic_read(&sdev->device_busy) >= sdev->queue_depth)
		return true;
	if (atomic_read(&sdev->device_blocked) > 0)
		return true;
	return false;
}