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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  tag; } ;
struct sbp_target_request {TYPE_1__ status; int /*<<< orphan*/  sense_buf; int /*<<< orphan*/  cmd_buf; TYPE_2__ se_cmd; int /*<<< orphan*/  orb_pointer; struct sbp_login_descriptor* login; } ;
struct sbp_session {int /*<<< orphan*/  se_sess; } ;
struct sbp_login_descriptor {int login_lun; struct sbp_session* sess; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  SBP_STATUS_UNSPECIFIED_ERROR ; 
 int STATUS_BLOCK_DEAD (int /*<<< orphan*/ ) ; 
 int STATUS_BLOCK_LEN (int) ; 
 int STATUS_BLOCK_RESP (int /*<<< orphan*/ ) ; 
 int STATUS_BLOCK_SBP_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_RESP_TRANSPORT_FAILURE ; 
 int /*<<< orphan*/  TARGET_SCF_ACK_KREF ; 
 int /*<<< orphan*/  TCM_SIMPLE_TAG ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  sbp_calc_data_length_direction (struct sbp_target_request*,int /*<<< orphan*/ *,int*) ; 
 int sbp_fetch_command (struct sbp_target_request*) ; 
 int sbp_fetch_page_table (struct sbp_target_request*) ; 
 int /*<<< orphan*/  sbp_send_status (struct sbp_target_request*) ; 
 scalar_t__ target_submit_cmd (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbp_handle_command(struct sbp_target_request *req)
{
	struct sbp_login_descriptor *login = req->login;
	struct sbp_session *sess = login->sess;
	int ret, unpacked_lun;
	u32 data_length;
	enum dma_data_direction data_dir;

	ret = sbp_fetch_command(req);
	if (ret) {
		pr_debug("sbp_handle_command: fetch command failed: %d\n", ret);
		goto err;
	}

	ret = sbp_fetch_page_table(req);
	if (ret) {
		pr_debug("sbp_handle_command: fetch page table failed: %d\n",
			ret);
		goto err;
	}

	unpacked_lun = req->login->login_lun;
	sbp_calc_data_length_direction(req, &data_length, &data_dir);

	pr_debug("sbp_handle_command ORB:0x%llx unpacked_lun:%d data_len:%d data_dir:%d\n",
			req->orb_pointer, unpacked_lun, data_length, data_dir);

	/* only used for printk until we do TMRs */
	req->se_cmd.tag = req->orb_pointer;
	if (target_submit_cmd(&req->se_cmd, sess->se_sess, req->cmd_buf,
			      req->sense_buf, unpacked_lun, data_length,
			      TCM_SIMPLE_TAG, data_dir, TARGET_SCF_ACK_KREF))
		goto err;

	return;

err:
	req->status.status |= cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_TRANSPORT_FAILURE) |
		STATUS_BLOCK_DEAD(0) |
		STATUS_BLOCK_LEN(1) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_UNSPECIFIED_ERROR));
	sbp_send_status(req);
}