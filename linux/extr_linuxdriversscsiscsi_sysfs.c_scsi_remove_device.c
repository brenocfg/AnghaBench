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
struct scsi_device {struct Scsi_Host* host; } ;
struct Scsi_Host {int /*<<< orphan*/  scan_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __scsi_remove_device (struct scsi_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void scsi_remove_device(struct scsi_device *sdev)
{
	struct Scsi_Host *shost = sdev->host;

	mutex_lock(&shost->scan_mutex);
	__scsi_remove_device(sdev);
	mutex_unlock(&shost->scan_mutex);
}