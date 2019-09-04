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
struct scsi_cmnd {int /*<<< orphan*/  result; int /*<<< orphan*/  sense_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_SOFT_ERROR ; 
 int /*<<< orphan*/  DRIVER_SENSE ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_driver_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

void zfcp_scsi_dif_sense_error(struct scsi_cmnd *scmd, int ascq)
{
	scsi_build_sense_buffer(1, scmd->sense_buffer,
				ILLEGAL_REQUEST, 0x10, ascq);
	set_driver_byte(scmd, DRIVER_SENSE);
	scmd->result |= SAM_STAT_CHECK_CONDITION;
	set_host_byte(scmd, DID_SOFT_ERROR);
}