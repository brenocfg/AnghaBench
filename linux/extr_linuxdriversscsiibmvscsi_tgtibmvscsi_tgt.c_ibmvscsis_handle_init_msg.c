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
struct scsi_info {int state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
#define  CONNECTED 142 
 long ERROR ; 
#define  ERR_DISCONNECT 141 
#define  ERR_DISCONNECTED 140 
#define  ERR_DISCONNECT_RECONNECT 139 
#define  H_CLOSED 138 
#define  H_DROPPED 137 
#define  H_PARAMETER 136 
#define  H_SUCCESS 135 
 int /*<<< orphan*/  INIT_COMPLETE_MSG ; 
#define  NO_QUEUE 134 
#define  SRP_PROCESSING 133 
#define  UNCONFIGURING 132 
#define  UNDEFINED 131 
#define  WAIT_CONNECTION 130 
#define  WAIT_ENABLED 129 
#define  WAIT_IDLE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int const,int /*<<< orphan*/ ) ; 
 long ibmvscsis_send_init_message (struct scsi_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ibmvscsis_handle_init_msg(struct scsi_info *vscsi)
{
	long rc = ADAPT_SUCCESS;

	switch (vscsi->state) {
	case WAIT_CONNECTION:
		rc = ibmvscsis_send_init_message(vscsi, INIT_COMPLETE_MSG);
		switch (rc) {
		case H_SUCCESS:
			vscsi->state = CONNECTED;
			break;

		case H_PARAMETER:
			dev_err(&vscsi->dev, "init_msg: failed to send, rc %ld\n",
				rc);
			ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT, 0);
			break;

		case H_DROPPED:
			dev_err(&vscsi->dev, "init_msg: failed to send, rc %ld\n",
				rc);
			rc = ERROR;
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
			break;

		case H_CLOSED:
			dev_warn(&vscsi->dev, "init_msg: failed to send, rc %ld\n",
				 rc);
			rc = 0;
			break;
		}
		break;

	case UNDEFINED:
		rc = ERROR;
		break;

	case UNCONFIGURING:
		break;

	case WAIT_ENABLED:
	case CONNECTED:
	case SRP_PROCESSING:
	case WAIT_IDLE:
	case NO_QUEUE:
	case ERR_DISCONNECT:
	case ERR_DISCONNECT_RECONNECT:
	case ERR_DISCONNECTED:
	default:
		rc = ERROR;
		dev_err(&vscsi->dev, "init_msg: invalid state %d to get init msg\n",
			vscsi->state);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		break;
	}

	return rc;
}