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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u64 ;
struct scsi_target {int /*<<< orphan*/  dev; } ;
struct scsi_device {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  scan_mutex; int /*<<< orphan*/  async_scan; struct device shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct scsi_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scsi_target* scsi_alloc_target (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_autopm_get_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_autopm_get_target (struct scsi_target*) ; 
 int /*<<< orphan*/  scsi_autopm_put_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_autopm_put_target (struct scsi_target*) ; 
 int /*<<< orphan*/  scsi_complete_async_scans () ; 
 scalar_t__ scsi_host_scan_allowed (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_probe_and_add_lun (struct scsi_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct scsi_device**,int,void*) ; 
 int /*<<< orphan*/  scsi_scan_type ; 
 int /*<<< orphan*/  scsi_target_reap (struct scsi_target*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

struct scsi_device *__scsi_add_device(struct Scsi_Host *shost, uint channel,
				      uint id, u64 lun, void *hostdata)
{
	struct scsi_device *sdev = ERR_PTR(-ENODEV);
	struct device *parent = &shost->shost_gendev;
	struct scsi_target *starget;

	if (strncmp(scsi_scan_type, "none", 4) == 0)
		return ERR_PTR(-ENODEV);

	starget = scsi_alloc_target(parent, channel, id);
	if (!starget)
		return ERR_PTR(-ENOMEM);
	scsi_autopm_get_target(starget);

	mutex_lock(&shost->scan_mutex);
	if (!shost->async_scan)
		scsi_complete_async_scans();

	if (scsi_host_scan_allowed(shost) && scsi_autopm_get_host(shost) == 0) {
		scsi_probe_and_add_lun(starget, lun, NULL, &sdev, 1, hostdata);
		scsi_autopm_put_host(shost);
	}
	mutex_unlock(&shost->scan_mutex);
	scsi_autopm_put_target(starget);
	/*
	 * paired with scsi_alloc_target().  Target will be destroyed unless
	 * scsi_probe_and_add_lun made an underlying device visible
	 */
	scsi_target_reap(starget);
	put_device(&starget->dev);

	return sdev;
}