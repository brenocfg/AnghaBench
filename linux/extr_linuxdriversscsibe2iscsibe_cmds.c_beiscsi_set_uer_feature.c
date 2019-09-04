#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mbox_mem; } ;
struct beiscsi_hba {int /*<<< orphan*/  state; int /*<<< orphan*/  ue2rp; struct be_ctrl_info ctrl; } ;
struct be_mcc_wrb {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ue2rp; } ;
struct TYPE_6__ {int /*<<< orphan*/  uer; } ;
struct TYPE_8__ {TYPE_3__ resp; TYPE_2__ req; } ;
struct TYPE_5__ {int /*<<< orphan*/  req_hdr; } ;
struct be_cmd_set_features {int param_len; TYPE_4__ param; int /*<<< orphan*/  feature; TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_UER_SUPP ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  BE_CMD_SET_FEATURE_UER ; 
 int /*<<< orphan*/  BE_CMD_UER_SUPP_BIT ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  EMBED_MBX_MAX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MCC_STATUS_ILLEGAL_REQUEST ; 
 int MCC_STATUS_INVALID_LENGTH ; 
 int /*<<< orphan*/  OPCODE_COMMON_SET_FEATURES ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct be_cmd_set_features* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int beiscsi_set_uer_feature(struct beiscsi_hba *phba)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_cmd_set_features *ioctl;
	struct be_mcc_wrb *wrb;
	int ret = 0;

	mutex_lock(&ctrl->mbox_lock);
	wrb = wrb_from_mbox(&ctrl->mbox_mem);
	memset(wrb, 0, sizeof(*wrb));
	ioctl = embedded_payload(wrb);

	be_wrb_hdr_prepare(wrb, sizeof(*ioctl), true, 0);
	be_cmd_hdr_prepare(&ioctl->h.req_hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_SET_FEATURES,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);
	ioctl->feature = BE_CMD_SET_FEATURE_UER;
	ioctl->param_len = sizeof(ioctl->param.req);
	ioctl->param.req.uer = BE_CMD_UER_SUPP_BIT;
	ret = be_mbox_notify(ctrl);
	if (!ret) {
		phba->ue2rp = ioctl->param.resp.ue2rp;
		set_bit(BEISCSI_HBA_UER_SUPP, &phba->state);
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : HBA error recovery supported\n");
	} else {
		/**
		 * Check "MCC_STATUS_INVALID_LENGTH" for SKH.
		 * Older FW versions return this error.
		 */
		if (ret == MCC_STATUS_ILLEGAL_REQUEST ||
		    ret == MCC_STATUS_INVALID_LENGTH)
			__beiscsi_log(phba, KERN_INFO,
				      "BG_%d : HBA error recovery not supported\n");
	}

	mutex_unlock(&ctrl->mbox_lock);
	return ret;
}