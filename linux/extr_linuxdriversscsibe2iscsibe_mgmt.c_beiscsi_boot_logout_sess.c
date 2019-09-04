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
struct TYPE_4__ {int /*<<< orphan*/  session_handle; } ;
struct TYPE_5__ {unsigned int tag; TYPE_1__ boot_sess; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; TYPE_3__* ptag_state; } ;
struct beiscsi_hba {TYPE_2__ boot_struct; struct be_ctrl_info ctrl; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_req_logout_fw_sess {int /*<<< orphan*/  session_handle; int /*<<< orphan*/  hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  cbfn; int /*<<< orphan*/  tag_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI_INI ; 
 int /*<<< orphan*/  MCC_TAG_STATE_ASYNC ; 
 int /*<<< orphan*/  OPCODE_ISCSI_INI_SESSION_LOGOUT_TARGET ; 
 struct be_mcc_wrb* alloc_mcc_wrb (struct beiscsi_hba*,unsigned int*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*,unsigned int) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_boot_process_compl ; 
 struct be_cmd_req_logout_fw_sess* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned int beiscsi_boot_logout_sess(struct beiscsi_hba *phba)
{
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_logout_fw_sess *req;
	unsigned int tag;

	mutex_lock(&ctrl->mbox_lock);
	wrb = alloc_mcc_wrb(phba, &tag);
	if (!wrb) {
		mutex_unlock(&ctrl->mbox_lock);
		return 0;
	}

	req = embedded_payload(wrb);
	be_wrb_hdr_prepare(wrb, sizeof(*req), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_SESSION_LOGOUT_TARGET,
			   sizeof(struct be_cmd_req_logout_fw_sess));
	/* Use the session handle copied into boot_sess */
	req->session_handle = phba->boot_struct.boot_sess.session_handle;

	phba->boot_struct.tag = tag;
	set_bit(MCC_TAG_STATE_ASYNC, &ctrl->ptag_state[tag].tag_state);
	ctrl->ptag_state[tag].cbfn = beiscsi_boot_process_compl;

	be_mcc_notify(phba, tag);
	mutex_unlock(&ctrl->mbox_lock);

	return tag;
}