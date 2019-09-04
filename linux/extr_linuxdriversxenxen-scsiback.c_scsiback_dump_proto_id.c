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
struct scsiback_tport {int tport_proto_id; } ;

/* Variables and functions */
#define  SCSI_PROTOCOL_FCP 130 
#define  SCSI_PROTOCOL_ISCSI 129 
#define  SCSI_PROTOCOL_SAS 128 

__attribute__((used)) static char *scsiback_dump_proto_id(struct scsiback_tport *tport)
{
	switch (tport->tport_proto_id) {
	case SCSI_PROTOCOL_SAS:
		return "SAS";
	case SCSI_PROTOCOL_FCP:
		return "FCP";
	case SCSI_PROTOCOL_ISCSI:
		return "iSCSI";
	default:
		break;
	}

	return "Unknown";
}