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
typedef  int u8 ;
typedef  int u16 ;
struct scsi_cmnd {int result; int /*<<< orphan*/  sense_buffer; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DRIVER_SENSE ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
#define  MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR 130 
#define  MPI2_IOCSTATUS_EEDP_GUARD_ERROR 129 
#define  MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR 128 
 int SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
_scsih_eedp_error_handling(struct scsi_cmnd *scmd, u16 ioc_status)
{
	u8 ascq;

	switch (ioc_status) {
	case MPI2_IOCSTATUS_EEDP_GUARD_ERROR:
		ascq = 0x01;
		break;
	case MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR:
		ascq = 0x02;
		break;
	case MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR:
		ascq = 0x03;
		break;
	default:
		ascq = 0x00;
		break;
	}
	scsi_build_sense_buffer(0, scmd->sense_buffer, ILLEGAL_REQUEST, 0x10,
	    ascq);
	scmd->result = DRIVER_SENSE << 24 | (DID_ABORT << 16) |
	    SAM_STAT_CHECK_CONDITION;
}