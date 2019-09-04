#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct slimbus_select_inst_req_msg_v01 {int instance; int mode_valid; int /*<<< orphan*/  mode; } ;
struct qmi_handle {int /*<<< orphan*/  sock; } ;
struct TYPE_4__ {struct qmi_handle* handle; int /*<<< orphan*/  svc_info; } ;
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dev; TYPE_2__ qmi; TYPE_1__* ngd; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SLIMBUS_MODE_MASTER_V01 ; 
 int /*<<< orphan*/  SLIMBUS_MODE_SATELLITE_V01 ; 
 int /*<<< orphan*/  SLIMBUS_QMI_POWER_REQ_MAX_MSG_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct qmi_handle*) ; 
 struct qmi_handle* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int kernel_connect (int /*<<< orphan*/ ,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_slim_qmi_msg_handlers ; 
 int qcom_slim_qmi_send_select_inst_req (struct qcom_slim_ngd_ctrl*,struct slimbus_select_inst_req_msg_v01*) ; 
 int qmi_handle_init (struct qmi_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmi_handle_release (struct qmi_handle*) ; 

__attribute__((used)) static int qcom_slim_qmi_init(struct qcom_slim_ngd_ctrl *ctrl,
			      bool apps_is_master)
{
	struct slimbus_select_inst_req_msg_v01 req;
	struct qmi_handle *handle;
	int rc;

	handle = devm_kzalloc(ctrl->dev, sizeof(*handle), GFP_KERNEL);
	if (!handle)
		return -ENOMEM;

	rc = qmi_handle_init(handle, SLIMBUS_QMI_POWER_REQ_MAX_MSG_LEN,
				NULL, qcom_slim_qmi_msg_handlers);
	if (rc < 0) {
		dev_err(ctrl->dev, "QMI client init failed: %d\n", rc);
		goto qmi_handle_init_failed;
	}

	rc = kernel_connect(handle->sock,
				(struct sockaddr *)&ctrl->qmi.svc_info,
				sizeof(ctrl->qmi.svc_info), 0);
	if (rc < 0) {
		dev_err(ctrl->dev, "Remote Service connect failed: %d\n", rc);
		goto qmi_connect_to_service_failed;
	}

	/* Instance is 0 based */
	req.instance = (ctrl->ngd->id >> 1);
	req.mode_valid = 1;

	/* Mode indicates the role of the ADSP */
	if (apps_is_master)
		req.mode = SLIMBUS_MODE_SATELLITE_V01;
	else
		req.mode = SLIMBUS_MODE_MASTER_V01;

	ctrl->qmi.handle = handle;

	rc = qcom_slim_qmi_send_select_inst_req(ctrl, &req);
	if (rc) {
		dev_err(ctrl->dev, "failed to select h/w instance\n");
		goto qmi_select_instance_failed;
	}

	return 0;

qmi_select_instance_failed:
	ctrl->qmi.handle = NULL;
qmi_connect_to_service_failed:
	qmi_handle_release(handle);
qmi_handle_init_failed:
	devm_kfree(ctrl->dev, handle);
	return rc;
}