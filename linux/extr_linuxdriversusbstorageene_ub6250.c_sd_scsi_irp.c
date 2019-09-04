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
struct us_data {scalar_t__ extra; } ;
struct scsi_cmnd {int* cmnd; } ;
struct ene_ub6250_info {int /*<<< orphan*/  SrbStatus; } ;

/* Variables and functions */
#define  INQUIRY 134 
#define  MODE_SENSE 133 
#define  READ_10 132 
#define  READ_CAPACITY 131 
#define  REQUEST_SENSE 130 
 int /*<<< orphan*/  SS_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SS_SUCCESS ; 
#define  TEST_UNIT_READY 129 
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
#define  WRITE_10 128 
 int do_scsi_inquiry (struct us_data*,struct scsi_cmnd*) ; 
 int do_scsi_request_sense (struct us_data*,struct scsi_cmnd*) ; 
 int sd_scsi_mode_sense (struct us_data*,struct scsi_cmnd*) ; 
 int sd_scsi_read (struct us_data*,struct scsi_cmnd*) ; 
 int sd_scsi_read_capacity (struct us_data*,struct scsi_cmnd*) ; 
 int sd_scsi_test_unit_ready (struct us_data*,struct scsi_cmnd*) ; 
 int sd_scsi_write (struct us_data*,struct scsi_cmnd*) ; 

__attribute__((used)) static int sd_scsi_irp(struct us_data *us, struct scsi_cmnd *srb)
{
	int    result;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *)us->extra;

	switch (srb->cmnd[0]) {
	case TEST_UNIT_READY:
		result = sd_scsi_test_unit_ready(us, srb);
		break; /* 0x00 */
	case REQUEST_SENSE:
		result = do_scsi_request_sense(us, srb);
		break; /* 0x03 */
	case INQUIRY:
		result = do_scsi_inquiry(us, srb);
		break; /* 0x12 */
	case MODE_SENSE:
		result = sd_scsi_mode_sense(us, srb);
		break; /* 0x1A */
	/*
	case START_STOP:
		result = SD_SCSI_Start_Stop(us, srb);
		break; //0x1B
	*/
	case READ_CAPACITY:
		result = sd_scsi_read_capacity(us, srb);
		break; /* 0x25 */
	case READ_10:
		result = sd_scsi_read(us, srb);
		break; /* 0x28 */
	case WRITE_10:
		result = sd_scsi_write(us, srb);
		break; /* 0x2A */
	default:
		info->SrbStatus = SS_ILLEGAL_REQUEST;
		result = USB_STOR_TRANSPORT_FAILED;
		break;
	}
	if (result == USB_STOR_TRANSPORT_GOOD)
		info->SrbStatus = SS_SUCCESS;
	return result;
}