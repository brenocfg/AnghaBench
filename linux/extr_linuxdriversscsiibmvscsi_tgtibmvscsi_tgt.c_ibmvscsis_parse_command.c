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
struct viosrp_crq {int valid; int /*<<< orphan*/  format; int /*<<< orphan*/  status; } ;
struct scsi_info {int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
#define  AIX_FORMAT 136 
 long ERROR ; 
 int /*<<< orphan*/  ERR_DISCONNECT_RECONNECT ; 
#define  LINUX_FORMAT 135 
#define  MAD_FORMAT 134 
#define  MESSAGE_IN_CRQ 133 
#define  OS400_FORMAT 132 
 int /*<<< orphan*/  PING ; 
 int PROCESSING_MAD ; 
 long SCHEDULE_DISCONNECT ; 
#define  SRP_FORMAT 131 
#define  VALID_CMD_RESP_EL 130 
#define  VALID_INIT_MSG 129 
#define  VALID_TRANS_EVENT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 long ibmvscsis_init_msg (struct scsi_info*,struct viosrp_crq*) ; 
 long ibmvscsis_mad (struct scsi_info*,struct viosrp_crq*) ; 
 int /*<<< orphan*/  ibmvscsis_ping_response (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_srp_cmd (struct scsi_info*,struct viosrp_crq*) ; 
 long ibmvscsis_trans_event (struct scsi_info*,struct viosrp_crq*) ; 

__attribute__((used)) static long ibmvscsis_parse_command(struct scsi_info *vscsi,
				    struct viosrp_crq *crq)
{
	long rc = ADAPT_SUCCESS;

	switch (crq->valid) {
	case VALID_CMD_RESP_EL:
		switch (crq->format) {
		case OS400_FORMAT:
		case AIX_FORMAT:
		case LINUX_FORMAT:
		case MAD_FORMAT:
			if (vscsi->flags & PROCESSING_MAD) {
				rc = ERROR;
				dev_err(&vscsi->dev, "parse_command: already processing mad\n");
				ibmvscsis_post_disconnect(vscsi,
						       ERR_DISCONNECT_RECONNECT,
						       0);
			} else {
				vscsi->flags |= PROCESSING_MAD;
				rc = ibmvscsis_mad(vscsi, crq);
			}
			break;

		case SRP_FORMAT:
			ibmvscsis_srp_cmd(vscsi, crq);
			break;

		case MESSAGE_IN_CRQ:
			if (crq->status == PING)
				ibmvscsis_ping_response(vscsi);
			break;

		default:
			dev_err(&vscsi->dev, "parse_command: invalid format %d\n",
				(uint)crq->format);
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
			break;
		}
		break;

	case VALID_TRANS_EVENT:
		rc = ibmvscsis_trans_event(vscsi, crq);
		break;

	case VALID_INIT_MSG:
		rc = ibmvscsis_init_msg(vscsi, crq);
		break;

	default:
		dev_err(&vscsi->dev, "parse_command: invalid valid field %d\n",
			(uint)crq->valid);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		break;
	}

	/*
	 * Return only what the interrupt handler cares
	 * about. Most errors we keep right on trucking.
	 */
	rc = vscsi->flags & SCHEDULE_DISCONNECT;

	return rc;
}