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
typedef  int u16 ;
struct nvmet_req {int data_len; TYPE_4__* sq; int /*<<< orphan*/  execute; TYPE_1__* ns; struct nvme_command* cmd; } ;
struct nvme_dsm_range {int dummy; } ;
struct TYPE_7__ {int opcode; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr; } ;
struct nvme_command {TYPE_3__ common; TYPE_2__ dsm; } ;
struct TYPE_8__ {int /*<<< orphan*/  qid; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffered_io; } ;

/* Variables and functions */
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_OPCODE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
#define  nvme_cmd_dsm 132 
#define  nvme_cmd_flush 131 
#define  nvme_cmd_read 130 
#define  nvme_cmd_write 129 
#define  nvme_cmd_write_zeroes 128 
 int /*<<< orphan*/  nvmet_file_execute_dsm ; 
 int /*<<< orphan*/  nvmet_file_execute_flush ; 
 int /*<<< orphan*/  nvmet_file_execute_rw ; 
 int /*<<< orphan*/  nvmet_file_execute_rw_buffered_io ; 
 int /*<<< orphan*/  nvmet_file_execute_write_zeroes ; 
 int nvmet_rw_len (struct nvmet_req*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

u16 nvmet_file_parse_io_cmd(struct nvmet_req *req)
{
	struct nvme_command *cmd = req->cmd;

	switch (cmd->common.opcode) {
	case nvme_cmd_read:
	case nvme_cmd_write:
		if (req->ns->buffered_io)
			req->execute = nvmet_file_execute_rw_buffered_io;
		else
			req->execute = nvmet_file_execute_rw;
		req->data_len = nvmet_rw_len(req);
		return 0;
	case nvme_cmd_flush:
		req->execute = nvmet_file_execute_flush;
		req->data_len = 0;
		return 0;
	case nvme_cmd_dsm:
		req->execute = nvmet_file_execute_dsm;
		req->data_len = (le32_to_cpu(cmd->dsm.nr) + 1) *
			sizeof(struct nvme_dsm_range);
		return 0;
	case nvme_cmd_write_zeroes:
		req->execute = nvmet_file_execute_write_zeroes;
		req->data_len = 0;
		return 0;
	default:
		pr_err("unhandled cmd for file ns %d on qid %d\n",
				cmd->common.opcode, req->sq->qid);
		return NVME_SC_INVALID_OPCODE | NVME_SC_DNR;
	}
}