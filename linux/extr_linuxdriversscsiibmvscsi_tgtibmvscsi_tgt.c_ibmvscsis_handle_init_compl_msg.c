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
#define  CONNECTED 138 
 long ERROR ; 
#define  ERR_DISCONNECT 137 
#define  ERR_DISCONNECTED 136 
#define  ERR_DISCONNECT_RECONNECT 135 
#define  NO_QUEUE 134 
#define  SRP_PROCESSING 133 
#define  UNCONFIGURING 132 
#define  UNDEFINED 131 
#define  WAIT_CONNECTION 130 
#define  WAIT_ENABLED 129 
#define  WAIT_IDLE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ibmvscsis_handle_init_compl_msg(struct scsi_info *vscsi)
{
	long rc = ADAPT_SUCCESS;

	switch (vscsi->state) {
	case NO_QUEUE:
	case ERR_DISCONNECT:
	case ERR_DISCONNECT_RECONNECT:
	case ERR_DISCONNECTED:
	case UNCONFIGURING:
	case UNDEFINED:
		rc = ERROR;
		break;

	case WAIT_CONNECTION:
		vscsi->state = CONNECTED;
		break;

	case WAIT_IDLE:
	case SRP_PROCESSING:
	case CONNECTED:
	case WAIT_ENABLED:
	default:
		rc = ERROR;
		dev_err(&vscsi->dev, "init_msg: invalid state %d to get init compl msg\n",
			vscsi->state);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		break;
	}

	return rc;
}