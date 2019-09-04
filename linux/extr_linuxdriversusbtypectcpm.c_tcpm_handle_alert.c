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
typedef  int /*<<< orphan*/  u32 ;
struct tcpm_port {int state; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  GET_STATUS_SEND ; 
 int /*<<< orphan*/  PD_MSG_CTRL_WAIT ; 
#define  SNK_READY 129 
#define  SRC_READY 128 
 unsigned int USB_PD_ADO_TYPE_BATT_STATUS_CHANGE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*) ; 
 int /*<<< orphan*/  tcpm_queue_message (struct tcpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_pd_ado_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcpm_handle_alert(struct tcpm_port *port, const __le32 *payload,
			      int cnt)
{
	u32 p0 = le32_to_cpu(payload[0]);
	unsigned int type = usb_pd_ado_type(p0);

	if (!type) {
		tcpm_log(port, "Alert message received with no type");
		return;
	}

	/* Just handling non-battery alerts for now */
	if (!(type & USB_PD_ADO_TYPE_BATT_STATUS_CHANGE)) {
		switch (port->state) {
		case SRC_READY:
		case SNK_READY:
			tcpm_set_state(port, GET_STATUS_SEND, 0);
			break;
		default:
			tcpm_queue_message(port, PD_MSG_CTRL_WAIT);
			break;
		}
	}
}