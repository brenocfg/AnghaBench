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
struct qcom_glink {int /*<<< orphan*/  dev; int /*<<< orphan*/  mbox_chan; } ;
struct glink_msg {int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  RPM_CMD_CLOSE 141 
#define  RPM_CMD_CLOSE_ACK 140 
#define  RPM_CMD_INTENT 139 
#define  RPM_CMD_OPEN 138 
#define  RPM_CMD_OPEN_ACK 137 
#define  RPM_CMD_READ_NOTIF 136 
#define  RPM_CMD_RX_DONE 135 
#define  RPM_CMD_RX_DONE_W_REUSE 134 
#define  RPM_CMD_RX_INTENT_REQ 133 
#define  RPM_CMD_RX_INTENT_REQ_ACK 132 
#define  RPM_CMD_TX_DATA 131 
#define  RPM_CMD_TX_DATA_CONT 130 
#define  RPM_CMD_VERSION 129 
#define  RPM_CMD_VERSION_ACK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_glink_handle_intent (struct qcom_glink*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qcom_glink_handle_intent_req_ack (struct qcom_glink*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qcom_glink_handle_rx_done (struct qcom_glink*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  qcom_glink_rx_advance (struct qcom_glink*,int /*<<< orphan*/ ) ; 
 unsigned int qcom_glink_rx_avail (struct qcom_glink*) ; 
 int qcom_glink_rx_data (struct qcom_glink*,unsigned int) ; 
 int qcom_glink_rx_defer (struct qcom_glink*,unsigned int) ; 
 int qcom_glink_rx_open_ack (struct qcom_glink*,unsigned int) ; 
 int /*<<< orphan*/  qcom_glink_rx_peak (struct qcom_glink*,struct glink_msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t qcom_glink_native_intr(int irq, void *data)
{
	struct qcom_glink *glink = data;
	struct glink_msg msg;
	unsigned int param1;
	unsigned int param2;
	unsigned int avail;
	unsigned int cmd;
	int ret = 0;

	for (;;) {
		avail = qcom_glink_rx_avail(glink);
		if (avail < sizeof(msg))
			break;

		qcom_glink_rx_peak(glink, &msg, 0, sizeof(msg));

		cmd = le16_to_cpu(msg.cmd);
		param1 = le16_to_cpu(msg.param1);
		param2 = le32_to_cpu(msg.param2);

		switch (cmd) {
		case RPM_CMD_VERSION:
		case RPM_CMD_VERSION_ACK:
		case RPM_CMD_CLOSE:
		case RPM_CMD_CLOSE_ACK:
		case RPM_CMD_RX_INTENT_REQ:
			ret = qcom_glink_rx_defer(glink, 0);
			break;
		case RPM_CMD_OPEN_ACK:
			ret = qcom_glink_rx_open_ack(glink, param1);
			qcom_glink_rx_advance(glink, ALIGN(sizeof(msg), 8));
			break;
		case RPM_CMD_OPEN:
			ret = qcom_glink_rx_defer(glink, param2);
			break;
		case RPM_CMD_TX_DATA:
		case RPM_CMD_TX_DATA_CONT:
			ret = qcom_glink_rx_data(glink, avail);
			break;
		case RPM_CMD_READ_NOTIF:
			qcom_glink_rx_advance(glink, ALIGN(sizeof(msg), 8));

			mbox_send_message(glink->mbox_chan, NULL);
			mbox_client_txdone(glink->mbox_chan, 0);
			break;
		case RPM_CMD_INTENT:
			qcom_glink_handle_intent(glink, param1, param2, avail);
			break;
		case RPM_CMD_RX_DONE:
			qcom_glink_handle_rx_done(glink, param1, param2, false);
			qcom_glink_rx_advance(glink, ALIGN(sizeof(msg), 8));
			break;
		case RPM_CMD_RX_DONE_W_REUSE:
			qcom_glink_handle_rx_done(glink, param1, param2, true);
			qcom_glink_rx_advance(glink, ALIGN(sizeof(msg), 8));
			break;
		case RPM_CMD_RX_INTENT_REQ_ACK:
			qcom_glink_handle_intent_req_ack(glink, param1, param2);
			qcom_glink_rx_advance(glink, ALIGN(sizeof(msg), 8));
			break;
		default:
			dev_err(glink->dev, "unhandled rx cmd: %d\n", cmd);
			ret = -EINVAL;
			break;
		}

		if (ret)
			break;
	}

	return IRQ_HANDLED;
}