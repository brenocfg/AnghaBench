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
struct iscsi_tm_rsp {int /*<<< orphan*/  response; int /*<<< orphan*/  itt; void* exp_cmdsn; void* max_cmdsn; int /*<<< orphan*/  opcode; } ;
struct iscsi_task {TYPE_3__* hdr; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct cqe {int dummy; } ;
struct bnx2i_tmf_response {int itt; int /*<<< orphan*/  response; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  max_cmd_sn; int /*<<< orphan*/  op_code; } ;
struct TYPE_5__ {int /*<<< orphan*/  resp_hdr; } ;
struct bnx2i_conn {TYPE_2__ gen_pdu; TYPE_1__* cls_conn; } ;
struct TYPE_6__ {int /*<<< orphan*/  itt; } ;
struct TYPE_4__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int ISCSI_TMF_RESPONSE_INDEX ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_tm_rsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_process_tmf_resp(struct iscsi_session *session,
				  struct bnx2i_conn *bnx2i_conn,
				  struct cqe *cqe)
{
	struct iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	struct iscsi_task *task;
	struct bnx2i_tmf_response *tmf_cqe;
	struct iscsi_tm_rsp *resp_hdr;

	tmf_cqe = (struct bnx2i_tmf_response *)cqe;
	spin_lock(&session->back_lock);
	task = iscsi_itt_to_task(conn,
				 tmf_cqe->itt & ISCSI_TMF_RESPONSE_INDEX);
	if (!task)
		goto done;

	resp_hdr = (struct iscsi_tm_rsp *) &bnx2i_conn->gen_pdu.resp_hdr;
	memset(resp_hdr, 0, sizeof(struct iscsi_hdr));
	resp_hdr->opcode = tmf_cqe->op_code;
	resp_hdr->max_cmdsn = cpu_to_be32(tmf_cqe->max_cmd_sn);
	resp_hdr->exp_cmdsn = cpu_to_be32(tmf_cqe->exp_cmd_sn);
	resp_hdr->itt = task->hdr->itt;
	resp_hdr->response = tmf_cqe->response;

	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)resp_hdr, NULL, 0);
done:
	spin_unlock(&session->back_lock);
	return 0;
}