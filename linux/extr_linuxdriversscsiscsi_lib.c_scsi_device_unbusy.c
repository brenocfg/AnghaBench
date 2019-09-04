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
struct scsi_target {scalar_t__ can_queue; int /*<<< orphan*/  target_busy; } ;
struct scsi_device {int /*<<< orphan*/  device_busy; struct Scsi_Host* host; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dec_host_busy (struct Scsi_Host*) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 

void scsi_device_unbusy(struct scsi_device *sdev)
{
	struct Scsi_Host *shost = sdev->host;
	struct scsi_target *starget = scsi_target(sdev);

	scsi_dec_host_busy(shost);

	if (starget->can_queue > 0)
		atomic_dec(&starget->target_busy);

	atomic_dec(&sdev->device_busy);
}