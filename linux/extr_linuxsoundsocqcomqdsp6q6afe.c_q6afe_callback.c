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
struct aprv2_ibasic_rsp_result_t {int /*<<< orphan*/  opcode; int /*<<< orphan*/  status; } ;
struct q6afe_port {int /*<<< orphan*/  refcount; int /*<<< orphan*/  wait; struct aprv2_ibasic_rsp_result_t result; } ;
struct q6afe {int /*<<< orphan*/  dev; } ;
struct apr_hdr {int opcode; int /*<<< orphan*/  token; } ;
struct apr_resp_pkt {struct aprv2_ibasic_rsp_result_t* payload; int /*<<< orphan*/  payload_size; struct apr_hdr hdr; } ;
struct apr_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AFE_PORT_CMD_DEVICE_START 132 
#define  AFE_PORT_CMD_DEVICE_STOP 131 
#define  AFE_PORT_CMD_SET_PARAM_V2 130 
#define  AFE_SVC_CMD_SET_PARAM 129 
#define  APR_BASIC_RSP_RESULT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct q6afe* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct q6afe_port* q6afe_find_port (struct q6afe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6afe_port_free ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6afe_callback(struct apr_device *adev, struct apr_resp_pkt *data)
{
	struct q6afe *afe = dev_get_drvdata(&adev->dev);
	struct aprv2_ibasic_rsp_result_t *res;
	struct apr_hdr *hdr = &data->hdr;
	struct q6afe_port *port;

	if (!data->payload_size)
		return 0;

	res = data->payload;
	switch (hdr->opcode) {
	case APR_BASIC_RSP_RESULT: {
		if (res->status) {
			dev_err(afe->dev, "cmd = 0x%x returned error = 0x%x\n",
				res->opcode, res->status);
		}
		switch (res->opcode) {
		case AFE_PORT_CMD_SET_PARAM_V2:
		case AFE_PORT_CMD_DEVICE_STOP:
		case AFE_PORT_CMD_DEVICE_START:
		case AFE_SVC_CMD_SET_PARAM:
			port = q6afe_find_port(afe, hdr->token);
			if (port) {
				port->result = *res;
				wake_up(&port->wait);
				kref_put(&port->refcount, q6afe_port_free);
			}
			break;
		default:
			dev_err(afe->dev, "Unknown cmd 0x%x\n",	res->opcode);
			break;
		}
	}
		break;
	default:
		break;
	}

	return 0;
}