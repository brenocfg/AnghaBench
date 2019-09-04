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
typedef  int /*<<< orphan*/  u64 ;
struct se_session {struct se_portal_group* se_tpg; } ;
struct se_portal_group {int /*<<< orphan*/  se_tpg_tfo; } ;
struct se_cmd {int /*<<< orphan*/  work; TYPE_1__* se_tmr_req; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  ref_task_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TARGET_SCF_ACK_KREF ; 
 int TARGET_SCF_LOOKUP_LUN_FROM_TAG ; 
 int /*<<< orphan*/  TCM_SIMPLE_TAG ; 
 unsigned char TMR_ABORT_TASK ; 
 int core_tmr_alloc_req (struct se_cmd*,void*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_tmr_release_req (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_complete_tmr_failure ; 
 int target_get_sess_cmd (struct se_cmd*,int) ; 
 int /*<<< orphan*/  target_lookup_lun_from_tag (struct se_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_generic_handle_tmr (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_init_se_cmd (struct se_cmd*,int /*<<< orphan*/ ,struct se_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int transport_lookup_tmr_lun (struct se_cmd*,int /*<<< orphan*/ ) ; 

int target_submit_tmr(struct se_cmd *se_cmd, struct se_session *se_sess,
		unsigned char *sense, u64 unpacked_lun,
		void *fabric_tmr_ptr, unsigned char tm_type,
		gfp_t gfp, u64 tag, int flags)
{
	struct se_portal_group *se_tpg;
	int ret;

	se_tpg = se_sess->se_tpg;
	BUG_ON(!se_tpg);

	transport_init_se_cmd(se_cmd, se_tpg->se_tpg_tfo, se_sess,
			      0, DMA_NONE, TCM_SIMPLE_TAG, sense);
	/*
	 * FIXME: Currently expect caller to handle se_cmd->se_tmr_req
	 * allocation failure.
	 */
	ret = core_tmr_alloc_req(se_cmd, fabric_tmr_ptr, tm_type, gfp);
	if (ret < 0)
		return -ENOMEM;

	if (tm_type == TMR_ABORT_TASK)
		se_cmd->se_tmr_req->ref_task_tag = tag;

	/* See target_submit_cmd for commentary */
	ret = target_get_sess_cmd(se_cmd, flags & TARGET_SCF_ACK_KREF);
	if (ret) {
		core_tmr_release_req(se_cmd->se_tmr_req);
		return ret;
	}
	/*
	 * If this is ABORT_TASK with no explicit fabric provided LUN,
	 * go ahead and search active session tags for a match to figure
	 * out unpacked_lun for the original se_cmd.
	 */
	if (tm_type == TMR_ABORT_TASK && (flags & TARGET_SCF_LOOKUP_LUN_FROM_TAG)) {
		if (!target_lookup_lun_from_tag(se_sess, tag, &unpacked_lun))
			goto failure;
	}

	ret = transport_lookup_tmr_lun(se_cmd, unpacked_lun);
	if (ret)
		goto failure;

	transport_generic_handle_tmr(se_cmd);
	return 0;

	/*
	 * For callback during failure handling, push this work off
	 * to process context with TMR_LUN_DOES_NOT_EXIST status.
	 */
failure:
	INIT_WORK(&se_cmd->work, target_complete_tmr_failure);
	schedule_work(&se_cmd->work);
	return 0;
}