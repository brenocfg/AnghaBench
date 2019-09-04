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
typedef  scalar_t__ u8 ;
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; int ascq; } ;
struct scsi_cmnd {int underflow; scalar_t__ result; int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  device; } ;
struct pqi_raid_error_info {scalar_t__ status; int data_out_result; int /*<<< orphan*/  data; int /*<<< orphan*/  response_data_length; int /*<<< orphan*/  sense_data_length; int /*<<< orphan*/  data_out_transferred; } ;
struct pqi_io_request {struct pqi_raid_error_info* error_info; struct scsi_cmnd* scmd; } ;

/* Variables and functions */
 scalar_t__ DID_ABORT ; 
 scalar_t__ DID_ERROR ; 
 scalar_t__ DID_NO_CONNECT ; 
 scalar_t__ DID_OK ; 
 scalar_t__ DID_SOFT_ERROR ; 
 scalar_t__ DID_TIME_OUT ; 
 scalar_t__ HARDWARE_ERROR ; 
#define  PQI_DATA_IN_OUT_ABORTED 148 
#define  PQI_DATA_IN_OUT_BUFFER_ERROR 147 
#define  PQI_DATA_IN_OUT_BUFFER_OVERFLOW 146 
#define  PQI_DATA_IN_OUT_BUFFER_OVERFLOW_BRIDGE 145 
#define  PQI_DATA_IN_OUT_BUFFER_OVERFLOW_DESCRIPTOR_AREA 144 
#define  PQI_DATA_IN_OUT_ERROR 143 
#define  PQI_DATA_IN_OUT_GOOD 142 
#define  PQI_DATA_IN_OUT_HARDWARE_ERROR 141 
#define  PQI_DATA_IN_OUT_PCIE_ACS_VIOLATION 140 
#define  PQI_DATA_IN_OUT_PCIE_COMPLETER_ABORT_RECEIVED 139 
#define  PQI_DATA_IN_OUT_PCIE_COMPLETION_TIMEOUT 138 
#define  PQI_DATA_IN_OUT_PCIE_ECRC_CHECK_FAILED 137 
#define  PQI_DATA_IN_OUT_PCIE_FABRIC_ERROR 136 
#define  PQI_DATA_IN_OUT_PCIE_POISONED_MEMORY_READ 135 
#define  PQI_DATA_IN_OUT_PCIE_TLP_PREFIX_BLOCKED 134 
#define  PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST 133 
#define  PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST_RECEIVED 132 
#define  PQI_DATA_IN_OUT_PROTOCOL_ERROR 131 
#define  PQI_DATA_IN_OUT_TIMEOUT 130 
#define  PQI_DATA_IN_OUT_UNDERFLOW 129 
#define  PQI_DATA_IN_OUT_UNSOLICITED_ABORT 128 
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 size_t SCSI_SENSE_BUFFERSIZE ; 
 size_t get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pqi_take_device_offline (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 scalar_t__ scsi_normalize_sense (int /*<<< orphan*/ ,size_t,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,scalar_t__) ; 

__attribute__((used)) static void pqi_process_raid_io_error(struct pqi_io_request *io_request)
{
	u8 scsi_status;
	u8 host_byte;
	struct scsi_cmnd *scmd;
	struct pqi_raid_error_info *error_info;
	size_t sense_data_length;
	int residual_count;
	int xfer_count;
	struct scsi_sense_hdr sshdr;

	scmd = io_request->scmd;
	if (!scmd)
		return;

	error_info = io_request->error_info;
	scsi_status = error_info->status;
	host_byte = DID_OK;

	switch (error_info->data_out_result) {
	case PQI_DATA_IN_OUT_GOOD:
		break;
	case PQI_DATA_IN_OUT_UNDERFLOW:
		xfer_count =
			get_unaligned_le32(&error_info->data_out_transferred);
		residual_count = scsi_bufflen(scmd) - xfer_count;
		scsi_set_resid(scmd, residual_count);
		if (xfer_count < scmd->underflow)
			host_byte = DID_SOFT_ERROR;
		break;
	case PQI_DATA_IN_OUT_UNSOLICITED_ABORT:
	case PQI_DATA_IN_OUT_ABORTED:
		host_byte = DID_ABORT;
		break;
	case PQI_DATA_IN_OUT_TIMEOUT:
		host_byte = DID_TIME_OUT;
		break;
	case PQI_DATA_IN_OUT_BUFFER_OVERFLOW:
	case PQI_DATA_IN_OUT_PROTOCOL_ERROR:
	case PQI_DATA_IN_OUT_BUFFER_ERROR:
	case PQI_DATA_IN_OUT_BUFFER_OVERFLOW_DESCRIPTOR_AREA:
	case PQI_DATA_IN_OUT_BUFFER_OVERFLOW_BRIDGE:
	case PQI_DATA_IN_OUT_ERROR:
	case PQI_DATA_IN_OUT_HARDWARE_ERROR:
	case PQI_DATA_IN_OUT_PCIE_FABRIC_ERROR:
	case PQI_DATA_IN_OUT_PCIE_COMPLETION_TIMEOUT:
	case PQI_DATA_IN_OUT_PCIE_COMPLETER_ABORT_RECEIVED:
	case PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST_RECEIVED:
	case PQI_DATA_IN_OUT_PCIE_ECRC_CHECK_FAILED:
	case PQI_DATA_IN_OUT_PCIE_UNSUPPORTED_REQUEST:
	case PQI_DATA_IN_OUT_PCIE_ACS_VIOLATION:
	case PQI_DATA_IN_OUT_PCIE_TLP_PREFIX_BLOCKED:
	case PQI_DATA_IN_OUT_PCIE_POISONED_MEMORY_READ:
	default:
		host_byte = DID_ERROR;
		break;
	}

	sense_data_length = get_unaligned_le16(&error_info->sense_data_length);
	if (sense_data_length == 0)
		sense_data_length =
			get_unaligned_le16(&error_info->response_data_length);
	if (sense_data_length) {
		if (sense_data_length > sizeof(error_info->data))
			sense_data_length = sizeof(error_info->data);

		if (scsi_status == SAM_STAT_CHECK_CONDITION &&
			scsi_normalize_sense(error_info->data,
				sense_data_length, &sshdr) &&
				sshdr.sense_key == HARDWARE_ERROR &&
				sshdr.asc == 0x3e &&
				sshdr.ascq == 0x1) {
			pqi_take_device_offline(scmd->device, "RAID");
			host_byte = DID_NO_CONNECT;
		}

		if (sense_data_length > SCSI_SENSE_BUFFERSIZE)
			sense_data_length = SCSI_SENSE_BUFFERSIZE;
		memcpy(scmd->sense_buffer, error_info->data,
			sense_data_length);
	}

	scmd->result = scsi_status;
	set_host_byte(scmd, host_byte);
}