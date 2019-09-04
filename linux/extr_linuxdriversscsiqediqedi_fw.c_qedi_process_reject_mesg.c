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
struct iscsi_reject_hdr {int hdr_second_dword; int max_cmd_sn; int exp_cmd_sn; int stat_sn; int /*<<< orphan*/  hdr_flags; int /*<<< orphan*/  hdr_reason; int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {struct iscsi_reject_hdr reject; } ;
struct TYPE_7__ {scalar_t__ cqe_type; TYPE_2__ iscsi_hdr; } ;
union iscsi_cqe {int /*<<< orphan*/  cqe_unsolicited; TYPE_3__ cqe_common; } ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u32 ;
struct qedi_ctx {int /*<<< orphan*/  hba_lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  resp_hdr; } ;
struct qedi_conn {TYPE_4__ gen_pdu; TYPE_1__* cls_conn; } ;
struct iscsi_task {int dummy; } ;
struct iscsi_session {int /*<<< orphan*/  back_lock; } ;
struct iscsi_reject {void* ffffffff; void* statsn; void* exp_cmdsn; void* max_cmdsn; int /*<<< orphan*/  dlength; int /*<<< orphan*/  flags; int /*<<< orphan*/  reason; int /*<<< orphan*/  opcode; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  data; struct iscsi_session* session; } ;
struct TYPE_5__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 scalar_t__ ISCSI_CQE_TYPE_UNSOLICITED ; 
 int ISCSI_REJECT_HDR_DATA_SEG_LEN_MASK ; 
 int QEDI_BDQ_BUF_SIZE ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_reject*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedi_unsol_pdu_adjust_bdq (struct qedi_ctx*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qedi_process_reject_mesg(struct qedi_ctx *qedi,
				     union iscsi_cqe *cqe,
				     struct iscsi_task *task,
				     struct qedi_conn *qedi_conn,
				     uint16_t que_idx)
{
	struct iscsi_conn *conn = qedi_conn->cls_conn->dd_data;
	struct iscsi_session *session = conn->session;
	struct iscsi_reject_hdr *cqe_reject;
	struct iscsi_reject *hdr;
	u32 pld_len, num_bdqs;
	unsigned long flags;

	spin_lock_bh(&session->back_lock);
	cqe_reject = &cqe->cqe_common.iscsi_hdr.reject;
	pld_len = cqe_reject->hdr_second_dword &
		  ISCSI_REJECT_HDR_DATA_SEG_LEN_MASK;
	num_bdqs = pld_len / QEDI_BDQ_BUF_SIZE;

	if (cqe->cqe_common.cqe_type == ISCSI_CQE_TYPE_UNSOLICITED) {
		spin_lock_irqsave(&qedi->hba_lock, flags);
		qedi_unsol_pdu_adjust_bdq(qedi, &cqe->cqe_unsolicited,
					  pld_len, num_bdqs, conn->data);
		spin_unlock_irqrestore(&qedi->hba_lock, flags);
	}
	hdr = (struct iscsi_reject *)&qedi_conn->gen_pdu.resp_hdr;
	memset(hdr, 0, sizeof(struct iscsi_hdr));
	hdr->opcode = cqe_reject->opcode;
	hdr->reason = cqe_reject->hdr_reason;
	hdr->flags = cqe_reject->hdr_flags;
	hton24(hdr->dlength, (cqe_reject->hdr_second_dword &
			      ISCSI_REJECT_HDR_DATA_SEG_LEN_MASK));
	hdr->max_cmdsn = cpu_to_be32(cqe_reject->max_cmd_sn);
	hdr->exp_cmdsn = cpu_to_be32(cqe_reject->exp_cmd_sn);
	hdr->statsn = cpu_to_be32(cqe_reject->stat_sn);
	hdr->ffffffff = cpu_to_be32(0xffffffff);

	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)hdr,
			     conn->data, pld_len);
	spin_unlock_bh(&session->back_lock);
}