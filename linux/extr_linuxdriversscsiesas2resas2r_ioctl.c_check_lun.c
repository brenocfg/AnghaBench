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
struct scsi_lun {scalar_t__* scsi_lun; } ;

/* Variables and functions */

__attribute__((used)) static bool check_lun(struct scsi_lun lun)
{
	bool result;

	result = ((lun.scsi_lun[7] == 0) &&
		  (lun.scsi_lun[6] == 0) &&
		  (lun.scsi_lun[5] == 0) &&
		  (lun.scsi_lun[4] == 0) &&
		  (lun.scsi_lun[3] == 0) &&
		  (lun.scsi_lun[2] == 0) &&
/* Byte 1 is intentionally skipped */
		  (lun.scsi_lun[0] == 0));

	return result;
}