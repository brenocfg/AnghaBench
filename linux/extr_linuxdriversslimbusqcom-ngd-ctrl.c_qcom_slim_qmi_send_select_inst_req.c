#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int result; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct slimbus_select_inst_resp_msg_v01 {TYPE_3__ resp; TYPE_1__ member_0; } ;
struct slimbus_select_inst_req_msg_v01 {int dummy; } ;
struct qmi_txn {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dev; TYPE_2__ qmi; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int QMI_RESULT_SUCCESS_V01 ; 
 int /*<<< orphan*/  SLIMBUS_QMI_RESP_TOUT ; 
 int /*<<< orphan*/  SLIMBUS_QMI_SELECT_INSTANCE_REQ_MAX_MSG_LEN ; 
 int /*<<< orphan*/  SLIMBUS_QMI_SELECT_INSTANCE_REQ_V01 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int qmi_send_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct slimbus_select_inst_req_msg_v01*) ; 
 int /*<<< orphan*/  qmi_txn_cancel (struct qmi_txn*) ; 
 int qmi_txn_init (int /*<<< orphan*/ ,struct qmi_txn*,int /*<<< orphan*/ ,struct slimbus_select_inst_resp_msg_v01*) ; 
 int qmi_txn_wait (struct qmi_txn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slimbus_select_inst_req_msg_v01_ei ; 
 int /*<<< orphan*/  slimbus_select_inst_resp_msg_v01_ei ; 

__attribute__((used)) static int qcom_slim_qmi_send_select_inst_req(struct qcom_slim_ngd_ctrl *ctrl,
				struct slimbus_select_inst_req_msg_v01 *req)
{
	struct slimbus_select_inst_resp_msg_v01 resp = { { 0, 0 } };
	struct qmi_txn txn;
	int rc;

	rc = qmi_txn_init(ctrl->qmi.handle, &txn,
				slimbus_select_inst_resp_msg_v01_ei, &resp);
	if (rc < 0) {
		dev_err(ctrl->dev, "QMI TXN init fail: %d\n", rc);
		return rc;
	}

	rc = qmi_send_request(ctrl->qmi.handle, NULL, &txn,
				SLIMBUS_QMI_SELECT_INSTANCE_REQ_V01,
				SLIMBUS_QMI_SELECT_INSTANCE_REQ_MAX_MSG_LEN,
				slimbus_select_inst_req_msg_v01_ei, req);
	if (rc < 0) {
		dev_err(ctrl->dev, "QMI send req fail %d\n", rc);
		qmi_txn_cancel(&txn);
		return rc;
	}

	rc = qmi_txn_wait(&txn, SLIMBUS_QMI_RESP_TOUT);
	if (rc < 0) {
		dev_err(ctrl->dev, "QMI TXN wait fail: %d\n", rc);
		return rc;
	}
	/* Check the response */
	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		dev_err(ctrl->dev, "QMI request failed 0x%x\n",
			resp.resp.result);
		return -EREMOTEIO;
	}

	return 0;
}