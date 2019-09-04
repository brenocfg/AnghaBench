#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcpm_port {int dummy; } ;
struct TYPE_2__ {int header; int* data; } ;
struct pd_message {TYPE_1__ ext_msg; int /*<<< orphan*/  header; } ;
typedef  enum pd_ext_msg_type { ____Placeholder_pd_ext_msg_type } pd_ext_msg_type ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PPS_STATUS_SEND ; 
#define  PD_EXT_BATT_CAP 141 
#define  PD_EXT_COUNTRY_CODES 140 
#define  PD_EXT_COUNTRY_INFO 139 
#define  PD_EXT_FW_UPDATE_REQUEST 138 
#define  PD_EXT_FW_UPDATE_RESPONSE 137 
#define  PD_EXT_GET_BATT_CAP 136 
#define  PD_EXT_GET_BATT_STATUS 135 
#define  PD_EXT_GET_MANUFACTURER_INFO 134 
 int PD_EXT_HDR_CHUNKED ; 
#define  PD_EXT_MANUFACTURER_INFO 133 
 unsigned int PD_EXT_MAX_CHUNK_DATA ; 
#define  PD_EXT_PPS_STATUS 132 
#define  PD_EXT_SECURITY_REQUEST 131 
#define  PD_EXT_SECURITY_RESPONSE 130 
#define  PD_EXT_SOURCE_CAP_EXT 129 
#define  PD_EXT_STATUS 128 
 int /*<<< orphan*/  PD_MSG_CTRL_NOT_SUPP ; 
 size_t USB_PD_EXT_SDB_EVENT_FLAGS ; 
 int USB_PD_EXT_SDB_PPS_EVENTS ; 
 unsigned int pd_ext_header_data_size_le (int) ; 
 int pd_header_type_le (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ready_state (struct tcpm_port*) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,...) ; 
 int /*<<< orphan*/  tcpm_queue_message (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcpm_pd_ext_msg_request(struct tcpm_port *port,
				    const struct pd_message *msg)
{
	enum pd_ext_msg_type type = pd_header_type_le(msg->header);
	unsigned int data_size = pd_ext_header_data_size_le(msg->ext_msg.header);

	if (!(msg->ext_msg.header & PD_EXT_HDR_CHUNKED)) {
		tcpm_log(port, "Unchunked extended messages unsupported");
		return;
	}

	if (data_size > PD_EXT_MAX_CHUNK_DATA) {
		tcpm_log(port, "Chunk handling not yet supported");
		return;
	}

	switch (type) {
	case PD_EXT_STATUS:
		/*
		 * If PPS related events raised then get PPS status to clear
		 * (see USB PD 3.0 Spec, 6.5.2.4)
		 */
		if (msg->ext_msg.data[USB_PD_EXT_SDB_EVENT_FLAGS] &
		    USB_PD_EXT_SDB_PPS_EVENTS)
			tcpm_set_state(port, GET_PPS_STATUS_SEND, 0);
		else
			tcpm_set_state(port, ready_state(port), 0);
		break;
	case PD_EXT_PPS_STATUS:
		/*
		 * For now the PPS status message is used to clear events
		 * and nothing more.
		 */
		tcpm_set_state(port, ready_state(port), 0);
		break;
	case PD_EXT_SOURCE_CAP_EXT:
	case PD_EXT_GET_BATT_CAP:
	case PD_EXT_GET_BATT_STATUS:
	case PD_EXT_BATT_CAP:
	case PD_EXT_GET_MANUFACTURER_INFO:
	case PD_EXT_MANUFACTURER_INFO:
	case PD_EXT_SECURITY_REQUEST:
	case PD_EXT_SECURITY_RESPONSE:
	case PD_EXT_FW_UPDATE_REQUEST:
	case PD_EXT_FW_UPDATE_RESPONSE:
	case PD_EXT_COUNTRY_INFO:
	case PD_EXT_COUNTRY_CODES:
		tcpm_queue_message(port, PD_MSG_CTRL_NOT_SUPP);
		break;
	default:
		tcpm_log(port, "Unhandled extended message type %#x", type);
		break;
	}
}