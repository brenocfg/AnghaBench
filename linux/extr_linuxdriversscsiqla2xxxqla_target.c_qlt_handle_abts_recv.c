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
struct scsi_qla_host {TYPE_2__* hw; } ;
struct rsp_que {int dummy; } ;
struct qla_tgt_sess_op {int /*<<< orphan*/  work; struct rsp_que* rsp; int /*<<< orphan*/  chip_reset; struct scsi_qla_host* vha; int /*<<< orphan*/  atio; } ;
typedef  int /*<<< orphan*/  response_t ;
struct TYPE_4__ {TYPE_1__* base_qpair; } ;
struct TYPE_3__ {int /*<<< orphan*/  chip_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qla_tgt_sess_op* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qla_tgt_wq ; 
 int /*<<< orphan*/  qlt_handle_abts_recv_work ; 
 int /*<<< orphan*/  qlt_response_pkt_all_vps (struct scsi_qla_host*,struct rsp_que*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qlt_handle_abts_recv(struct scsi_qla_host *vha, struct rsp_que *rsp,
    response_t *pkt)
{
	struct qla_tgt_sess_op *op;

	op = kzalloc(sizeof(*op), GFP_ATOMIC);

	if (!op) {
		/* do not reach for ATIO queue here.  This is best effort err
		 * recovery at this point.
		 */
		qlt_response_pkt_all_vps(vha, rsp, pkt);
		return;
	}

	memcpy(&op->atio, pkt, sizeof(*pkt));
	op->vha = vha;
	op->chip_reset = vha->hw->base_qpair->chip_reset;
	op->rsp = rsp;
	INIT_WORK(&op->work, qlt_handle_abts_recv_work);
	queue_work(qla_tgt_wq, &op->work);
	return;
}