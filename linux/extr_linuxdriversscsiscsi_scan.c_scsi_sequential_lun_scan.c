#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {TYPE_1__ dev; } ;
struct Scsi_Host {int max_lun; } ;
typedef  enum scsi_scan_mode { ____Placeholder_scsi_scan_mode } scsi_scan_mode ;
typedef  int blist_flags_t ;

/* Variables and functions */
 int BLIST_FORCELUN ; 
 int BLIST_LARGELUN ; 
 int BLIST_MAX5LUN ; 
 int BLIST_SPARSELUN ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_3 ; 
 int /*<<< orphan*/  SCSI_LOG_SCAN_BUS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SCSI_SCAN_LUN_PRESENT ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 unsigned int max_scsi_luns ; 
 int min (unsigned int,int) ; 
 scalar_t__ scsi_probe_and_add_lun (struct scsi_target*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  starget_printk (int /*<<< orphan*/ ,struct scsi_target*,char*) ; 

__attribute__((used)) static void scsi_sequential_lun_scan(struct scsi_target *starget,
				     blist_flags_t bflags, int scsi_level,
				     enum scsi_scan_mode rescan)
{
	uint max_dev_lun;
	u64 sparse_lun, lun;
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);

	SCSI_LOG_SCAN_BUS(3, starget_printk(KERN_INFO, starget,
		"scsi scan: Sequential scan\n"));

	max_dev_lun = min(max_scsi_luns, shost->max_lun);
	/*
	 * If this device is known to support sparse multiple units,
	 * override the other settings, and scan all of them. Normally,
	 * SCSI-3 devices should be scanned via the REPORT LUNS.
	 */
	if (bflags & BLIST_SPARSELUN) {
		max_dev_lun = shost->max_lun;
		sparse_lun = 1;
	} else
		sparse_lun = 0;

	/*
	 * If less than SCSI_1_CCS, and no special lun scanning, stop
	 * scanning; this matches 2.4 behaviour, but could just be a bug
	 * (to continue scanning a SCSI_1_CCS device).
	 *
	 * This test is broken.  We might not have any device on lun0 for
	 * a sparselun device, and if that's the case then how would we
	 * know the real scsi_level, eh?  It might make sense to just not
	 * scan any SCSI_1 device for non-0 luns, but that check would best
	 * go into scsi_alloc_sdev() and just have it return null when asked
	 * to alloc an sdev for lun > 0 on an already found SCSI_1 device.
	 *
	if ((sdevscan->scsi_level < SCSI_1_CCS) &&
	    ((bflags & (BLIST_FORCELUN | BLIST_SPARSELUN | BLIST_MAX5LUN))
	     == 0))
		return;
	 */
	/*
	 * If this device is known to support multiple units, override
	 * the other settings, and scan all of them.
	 */
	if (bflags & BLIST_FORCELUN)
		max_dev_lun = shost->max_lun;
	/*
	 * REGAL CDC-4X: avoid hang after LUN 4
	 */
	if (bflags & BLIST_MAX5LUN)
		max_dev_lun = min(5U, max_dev_lun);
	/*
	 * Do not scan SCSI-2 or lower device past LUN 7, unless
	 * BLIST_LARGELUN.
	 */
	if (scsi_level < SCSI_3 && !(bflags & BLIST_LARGELUN))
		max_dev_lun = min(8U, max_dev_lun);
	else
		max_dev_lun = min(256U, max_dev_lun);

	/*
	 * We have already scanned LUN 0, so start at LUN 1. Keep scanning
	 * until we reach the max, or no LUN is found and we are not
	 * sparse_lun.
	 */
	for (lun = 1; lun < max_dev_lun; ++lun)
		if ((scsi_probe_and_add_lun(starget, lun, NULL, NULL, rescan,
					    NULL) != SCSI_SCAN_LUN_PRESENT) &&
		    !sparse_lun)
			return;
}