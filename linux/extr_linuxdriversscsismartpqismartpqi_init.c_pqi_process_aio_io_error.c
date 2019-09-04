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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {int underflow; int /*<<< orphan*/  result; int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  device; } ;
struct pqi_io_request {int /*<<< orphan*/  raid_bypass; int /*<<< orphan*/  status; struct pqi_aio_error_info* error_info; struct scsi_cmnd* scmd; } ;
struct pqi_aio_error_info {int service_response; int /*<<< orphan*/  data; int /*<<< orphan*/  data_length; scalar_t__ data_present; int /*<<< orphan*/  residual_count; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  DID_OK ; 
 int /*<<< orphan*/  DID_SOFT_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  HARDWARE_ERROR ; 
#define  PQI_AIO_SERV_RESPONSE_COMPLETE 140 
#define  PQI_AIO_SERV_RESPONSE_FAILURE 139 
#define  PQI_AIO_SERV_RESPONSE_TMF_COMPLETE 138 
#define  PQI_AIO_SERV_RESPONSE_TMF_INCORRECT_LUN 137 
#define  PQI_AIO_SERV_RESPONSE_TMF_REJECTED 136 
#define  PQI_AIO_SERV_RESPONSE_TMF_SUCCEEDED 135 
#define  PQI_AIO_STATUS_AIO_PATH_DISABLED 134 
#define  PQI_AIO_STATUS_INVALID_DEVICE 133 
#define  PQI_AIO_STATUS_IO_ABORTED 132 
#define  PQI_AIO_STATUS_IO_ERROR 131 
#define  PQI_AIO_STATUS_NO_PATH_TO_DEVICE 130 
#define  PQI_AIO_STATUS_OVERRUN 129 
#define  PQI_AIO_STATUS_UNDERRUN 128 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  SAM_STAT_TASK_ABORTED ; 
 size_t SCSI_SENSE_BUFFERSIZE ; 
 size_t get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pqi_aio_path_disabled (struct pqi_io_request*) ; 
 int /*<<< orphan*/  pqi_take_device_offline (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_process_aio_io_error(struct pqi_io_request *io_request)
{
	u8 scsi_status;
	u8 host_byte;
	struct scsi_cmnd *scmd;
	struct pqi_aio_error_info *error_info;
	size_t sense_data_length;
	int residual_count;
	int xfer_count;
	bool device_offline;

	scmd = io_request->scmd;
	error_info = io_request->error_info;
	host_byte = DID_OK;
	sense_data_length = 0;
	device_offline = false;

	switch (error_info->service_response) {
	case PQI_AIO_SERV_RESPONSE_COMPLETE:
		scsi_status = error_info->status;
		break;
	case PQI_AIO_SERV_RESPONSE_FAILURE:
		switch (error_info->status) {
		case PQI_AIO_STATUS_IO_ABORTED:
			scsi_status = SAM_STAT_TASK_ABORTED;
			break;
		case PQI_AIO_STATUS_UNDERRUN:
			scsi_status = SAM_STAT_GOOD;
			residual_count = get_unaligned_le32(
						&error_info->residual_count);
			scsi_set_resid(scmd, residual_count);
			xfer_count = scsi_bufflen(scmd) - residual_count;
			if (xfer_count < scmd->underflow)
				host_byte = DID_SOFT_ERROR;
			break;
		case PQI_AIO_STATUS_OVERRUN:
			scsi_status = SAM_STAT_GOOD;
			break;
		case PQI_AIO_STATUS_AIO_PATH_DISABLED:
			pqi_aio_path_disabled(io_request);
			scsi_status = SAM_STAT_GOOD;
			io_request->status = -EAGAIN;
			break;
		case PQI_AIO_STATUS_NO_PATH_TO_DEVICE:
		case PQI_AIO_STATUS_INVALID_DEVICE:
			if (!io_request->raid_bypass) {
				device_offline = true;
				pqi_take_device_offline(scmd->device, "AIO");
				host_byte = DID_NO_CONNECT;
			}
			scsi_status = SAM_STAT_CHECK_CONDITION;
			break;
		case PQI_AIO_STATUS_IO_ERROR:
		default:
			scsi_status = SAM_STAT_CHECK_CONDITION;
			break;
		}
		break;
	case PQI_AIO_SERV_RESPONSE_TMF_COMPLETE:
	case PQI_AIO_SERV_RESPONSE_TMF_SUCCEEDED:
		scsi_status = SAM_STAT_GOOD;
		break;
	case PQI_AIO_SERV_RESPONSE_TMF_REJECTED:
	case PQI_AIO_SERV_RESPONSE_TMF_INCORRECT_LUN:
	default:
		scsi_status = SAM_STAT_CHECK_CONDITION;
		break;
	}

	if (error_info->data_present) {
		sense_data_length =
			get_unaligned_le16(&error_info->data_length);
		if (sense_data_length) {
			if (sense_data_length > sizeof(error_info->data))
				sense_data_length = sizeof(error_info->data);
			if (sense_data_length > SCSI_SENSE_BUFFERSIZE)
				sense_data_length = SCSI_SENSE_BUFFERSIZE;
			memcpy(scmd->sense_buffer, error_info->data,
				sense_data_length);
		}
	}

	if (device_offline && sense_data_length == 0)
		scsi_build_sense_buffer(0, scmd->sense_buffer, HARDWARE_ERROR,
			0x3e, 0x1);

	scmd->result = scsi_status;
	set_host_byte(scmd, host_byte);
}