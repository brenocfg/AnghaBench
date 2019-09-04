#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  counter; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; TYPE_2__* bus; TYPE_1__ enable_cnt; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct esas2r_request {int dummy; } ;
struct esas2r_adapter {int sysfs_fw_created; int sysfs_fs_created; int sysfs_vda_created; int sysfs_hw_created; int sysfs_live_nvram_created; int sysfs_default_nvram_created; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {int max_lun; int max_cmd_len; int /*<<< orphan*/  shost_gendev; TYPE_3__ shost_dev; scalar_t__ hostdata; int /*<<< orphan*/  max_sectors; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  unique_id; scalar_t__ max_channel; scalar_t__ max_id; scalar_t__ this_id; int /*<<< orphan*/  cmd_per_lun; int /*<<< orphan*/  can_queue; } ;
typedef  int num_requests ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  ESAS2R_LOG_DEBG ; 
 int /*<<< orphan*/  ESAS2R_LOG_INFO ; 
 int /*<<< orphan*/  ESAS2R_LOG_WARN ; 
 scalar_t__ ESAS2R_MAX_ID ; 
 int /*<<< orphan*/  bin_attr_default_nvram ; 
 int /*<<< orphan*/  bin_attr_fs ; 
 int /*<<< orphan*/  bin_attr_fw ; 
 int /*<<< orphan*/  bin_attr_hw ; 
 int /*<<< orphan*/  bin_attr_live_nvram ; 
 int /*<<< orphan*/  bin_attr_vda ; 
 int /*<<< orphan*/  can_queue ; 
 int /*<<< orphan*/  cmd_per_lun ; 
 int /*<<< orphan*/  driver_template ; 
 int /*<<< orphan*/  esas2r_fw_event_on (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_init_adapter (struct Scsi_Host*,struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  esas2r_log_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  esas2r_max_sectors ; 
 int /*<<< orphan*/  found_adapters ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sg_tablesize ; 
 scalar_t__ sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esas2r_probe(struct pci_dev *pcid,
			const struct pci_device_id *id)
{
	struct Scsi_Host *host = NULL;
	struct esas2r_adapter *a;
	int err;

	size_t host_alloc_size = sizeof(struct esas2r_adapter)
				 + ((num_requests) +
				    1) * sizeof(struct esas2r_request);

	esas2r_log_dev(ESAS2R_LOG_DEBG, &(pcid->dev),
		       "esas2r_probe() 0x%02x 0x%02x 0x%02x 0x%02x",
		       pcid->vendor,
		       pcid->device,
		       pcid->subsystem_vendor,
		       pcid->subsystem_device);

	esas2r_log_dev(ESAS2R_LOG_INFO, &(pcid->dev),
		       "before pci_enable_device() "
		       "enable_cnt: %d",
		       pcid->enable_cnt.counter);

	err = pci_enable_device(pcid);
	if (err != 0) {
		esas2r_log_dev(ESAS2R_LOG_CRIT, &(pcid->dev),
			       "pci_enable_device() FAIL (%d)",
			       err);
		return -ENODEV;
	}

	esas2r_log_dev(ESAS2R_LOG_INFO, &(pcid->dev),
		       "pci_enable_device() OK");
	esas2r_log_dev(ESAS2R_LOG_INFO, &(pcid->dev),
		       "after pci_enable_device() enable_cnt: %d",
		       pcid->enable_cnt.counter);

	host = scsi_host_alloc(&driver_template, host_alloc_size);
	if (host == NULL) {
		esas2r_log(ESAS2R_LOG_CRIT, "scsi_host_alloc() FAIL");
		return -ENODEV;
	}

	memset(host->hostdata, 0, host_alloc_size);

	a = (struct esas2r_adapter *)host->hostdata;

	esas2r_log(ESAS2R_LOG_INFO, "scsi_host_alloc() OK host: %p", host);

	/* override max LUN and max target id */

	host->max_id = ESAS2R_MAX_ID + 1;
	host->max_lun = 255;

	/* we can handle 16-byte CDbs */

	host->max_cmd_len = 16;

	host->can_queue = can_queue;
	host->cmd_per_lun = cmd_per_lun;
	host->this_id = host->max_id + 1;
	host->max_channel = 0;
	host->unique_id = found_adapters;
	host->sg_tablesize = sg_tablesize;
	host->max_sectors = esas2r_max_sectors;

	/* set to bus master for BIOses that don't do it for us */

	esas2r_log(ESAS2R_LOG_INFO, "pci_set_master() called");

	pci_set_master(pcid);

	if (!esas2r_init_adapter(host, pcid, found_adapters)) {
		esas2r_log(ESAS2R_LOG_CRIT,
			   "unable to initialize device at PCI bus %x:%x",
			   pcid->bus->number,
			   pcid->devfn);

		esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
			       "scsi_host_put() called");

		scsi_host_put(host);

		return 0;

	}

	esas2r_log(ESAS2R_LOG_INFO, "pci_set_drvdata(%p, %p) called", pcid,
		   host->hostdata);

	pci_set_drvdata(pcid, host);

	esas2r_log(ESAS2R_LOG_INFO, "scsi_add_host() called");

	err = scsi_add_host(host, &pcid->dev);

	if (err) {
		esas2r_log(ESAS2R_LOG_CRIT, "scsi_add_host returned %d", err);
		esas2r_log_dev(ESAS2R_LOG_CRIT, &(host->shost_gendev),
			       "scsi_add_host() FAIL");

		esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
			       "scsi_host_put() called");

		scsi_host_put(host);

		esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
			       "pci_set_drvdata(%p, NULL) called",
			       pcid);

		pci_set_drvdata(pcid, NULL);

		return -ENODEV;
	}


	esas2r_fw_event_on(a);

	esas2r_log_dev(ESAS2R_LOG_INFO, &(host->shost_gendev),
		       "scsi_scan_host() called");

	scsi_scan_host(host);

	/* Add sysfs binary files */
	if (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_fw))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: fw");
	else
		a->sysfs_fw_created = 1;

	if (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_fs))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: fs");
	else
		a->sysfs_fs_created = 1;

	if (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_vda))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: vda");
	else
		a->sysfs_vda_created = 1;

	if (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_hw))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: hw");
	else
		a->sysfs_hw_created = 1;

	if (sysfs_create_bin_file(&host->shost_dev.kobj, &bin_attr_live_nvram))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: live_nvram");
	else
		a->sysfs_live_nvram_created = 1;

	if (sysfs_create_bin_file(&host->shost_dev.kobj,
				  &bin_attr_default_nvram))
		esas2r_log_dev(ESAS2R_LOG_WARN, &(host->shost_gendev),
			       "Failed to create sysfs binary file: default_nvram");
	else
		a->sysfs_default_nvram_created = 1;

	found_adapters++;

	return 0;
}