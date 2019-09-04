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
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mbox_mem; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct be_mcc_wrb {int dummy; } ;
struct TYPE_5__ {scalar_t__ param_len; scalar_t__ param_data; int /*<<< orphan*/  param_id; } ;
struct TYPE_6__ {TYPE_2__ req; } ;
struct TYPE_4__ {int /*<<< orphan*/  req_hdr; } ;
struct be_cmd_set_host_data {TYPE_3__ param; TYPE_1__ h; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 scalar_t__ BE_CMD_MAX_DRV_VERSION ; 
 int /*<<< orphan*/  BE_CMD_SET_HOST_PARAM_ID ; 
 char* BUILD_STR ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  EMBED_MBX_MAX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MCC_STATUS_ILLEGAL_REQUEST ; 
 int MCC_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  OPCODE_COMMON_SET_HOST_DATA ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct be_cmd_set_host_data* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ is_chip_be2_be3r (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int beiscsi_set_host_data(struct beiscsi_hba *phba)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_cmd_set_host_data *ioctl;
	struct be_mcc_wrb *wrb;
	int ret = 0;

	if (is_chip_be2_be3r(phba))
		return ret;

	mutex_lock(&ctrl->mbox_lock);
	wrb = wrb_from_mbox(&ctrl->mbox_mem);
	memset(wrb, 0, sizeof(*wrb));
	ioctl = embedded_payload(wrb);

	be_wrb_hdr_prepare(wrb, sizeof(*ioctl), true, 0);
	be_cmd_hdr_prepare(&ioctl->h.req_hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_SET_HOST_DATA,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);
	ioctl->param.req.param_id = BE_CMD_SET_HOST_PARAM_ID;
	ioctl->param.req.param_len =
		snprintf((char *)ioctl->param.req.param_data,
			 sizeof(ioctl->param.req.param_data),
			 "Linux iSCSI v%s", BUILD_STR);
	ioctl->param.req.param_len = ALIGN(ioctl->param.req.param_len + 1, 4);
	if (ioctl->param.req.param_len > BE_CMD_MAX_DRV_VERSION)
		ioctl->param.req.param_len = BE_CMD_MAX_DRV_VERSION;
	ret = be_mbox_notify(ctrl);
	if (!ret) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : HBA set host driver version\n");
	} else {
		/**
		 * Check "MCC_STATUS_INVALID_LENGTH" for SKH.
		 * Older FW versions return this error.
		 */
		if (ret == MCC_STATUS_ILLEGAL_REQUEST ||
				ret == MCC_STATUS_INVALID_LENGTH)
			__beiscsi_log(phba, KERN_INFO,
				      "BG_%d : HBA failed to set host driver version\n");
	}

	mutex_unlock(&ctrl->mbox_lock);
	return ret;
}