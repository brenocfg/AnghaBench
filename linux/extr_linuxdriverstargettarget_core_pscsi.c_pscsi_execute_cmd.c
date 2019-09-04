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
struct se_cmd {scalar_t__ data_direction; scalar_t__ sam_task_attr; int /*<<< orphan*/ * t_task_cdb; struct pscsi_plugin_task* priv; int /*<<< orphan*/  se_dev; int /*<<< orphan*/  t_data_nents; struct scatterlist* t_data_sg; } ;
struct scatterlist {int dummy; } ;
struct request {int /*<<< orphan*/  timeout; struct se_cmd* end_io_data; int /*<<< orphan*/  end_io; } ;
struct pscsi_plugin_task {int /*<<< orphan*/ * pscsi_cdb; } ;
struct pscsi_dev_virt {TYPE_1__* pdv_sd; } ;
typedef  scalar_t__ sense_reason_t ;
struct TYPE_4__ {int /*<<< orphan*/  retries; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  cmd_len; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct request*) ; 
 struct pscsi_dev_virt* PSCSI_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_RETRY ; 
 int /*<<< orphan*/  PS_TIMEOUT_DISK ; 
 int /*<<< orphan*/  PS_TIMEOUT_OTHER ; 
 int /*<<< orphan*/  REQ_OP_SCSI_IN ; 
 int /*<<< orphan*/  REQ_OP_SCSI_OUT ; 
 scalar_t__ TCM_HEAD_TAG ; 
 scalar_t__ TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_ZBC ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  kfree (struct pscsi_plugin_task*) ; 
 struct pscsi_plugin_task* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ pscsi_map_sg (struct se_cmd*,struct scatterlist*,int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  pscsi_req_done ; 
 int /*<<< orphan*/  scsi_command_size (int /*<<< orphan*/ *) ; 
 TYPE_2__* scsi_req (struct request*) ; 

__attribute__((used)) static sense_reason_t
pscsi_execute_cmd(struct se_cmd *cmd)
{
	struct scatterlist *sgl = cmd->t_data_sg;
	u32 sgl_nents = cmd->t_data_nents;
	struct pscsi_dev_virt *pdv = PSCSI_DEV(cmd->se_dev);
	struct pscsi_plugin_task *pt;
	struct request *req;
	sense_reason_t ret;

	/*
	 * Dynamically alloc cdb space, since it may be larger than
	 * TCM_MAX_COMMAND_SIZE
	 */
	pt = kzalloc(sizeof(*pt) + scsi_command_size(cmd->t_task_cdb), GFP_KERNEL);
	if (!pt) {
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}
	cmd->priv = pt;

	memcpy(pt->pscsi_cdb, cmd->t_task_cdb,
		scsi_command_size(cmd->t_task_cdb));

	req = blk_get_request(pdv->pdv_sd->request_queue,
			cmd->data_direction == DMA_TO_DEVICE ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	if (IS_ERR(req)) {
		pr_err("PSCSI: blk_get_request() failed\n");
		ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		goto fail;
	}

	if (sgl) {
		ret = pscsi_map_sg(cmd, sgl, sgl_nents, req);
		if (ret)
			goto fail_put_request;
	}

	req->end_io = pscsi_req_done;
	req->end_io_data = cmd;
	scsi_req(req)->cmd_len = scsi_command_size(pt->pscsi_cdb);
	scsi_req(req)->cmd = &pt->pscsi_cdb[0];
	if (pdv->pdv_sd->type == TYPE_DISK ||
	    pdv->pdv_sd->type == TYPE_ZBC)
		req->timeout = PS_TIMEOUT_DISK;
	else
		req->timeout = PS_TIMEOUT_OTHER;
	scsi_req(req)->retries = PS_RETRY;

	blk_execute_rq_nowait(pdv->pdv_sd->request_queue, NULL, req,
			(cmd->sam_task_attr == TCM_HEAD_TAG),
			pscsi_req_done);

	return 0;

fail_put_request:
	blk_put_request(req);
fail:
	kfree(pt);
	return ret;
}