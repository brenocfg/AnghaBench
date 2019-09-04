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
struct scsi_disk {int /*<<< orphan*/  dev; struct scsi_device* device; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  sd_ref_mutex ; 

__attribute__((used)) static void scsi_disk_put(struct scsi_disk *sdkp)
{
	struct scsi_device *sdev = sdkp->device;

	mutex_lock(&sd_ref_mutex);
	put_device(&sdkp->dev);
	scsi_device_put(sdev);
	mutex_unlock(&sd_ref_mutex);
}