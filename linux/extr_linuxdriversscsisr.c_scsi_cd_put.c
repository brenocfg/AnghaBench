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
struct scsi_device {int dummy; } ;
struct scsi_cd {int /*<<< orphan*/  kref; struct scsi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  sr_kref_release ; 
 int /*<<< orphan*/  sr_ref_mutex ; 

__attribute__((used)) static void scsi_cd_put(struct scsi_cd *cd)
{
	struct scsi_device *sdev = cd->device;

	mutex_lock(&sr_ref_mutex);
	kref_put(&cd->kref, sr_kref_release);
	scsi_device_put(sdev);
	mutex_unlock(&sr_ref_mutex);
}