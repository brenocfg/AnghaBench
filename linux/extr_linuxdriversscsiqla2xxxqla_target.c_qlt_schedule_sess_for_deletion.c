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
struct qla_tgt {scalar_t__ sess_count; int /*<<< orphan*/  waitQ; scalar_t__ tgt_stop; } ;
struct fc_port {scalar_t__ disc_state; scalar_t__ deleted; int /*<<< orphan*/  del_work; TYPE_2__* vha; int /*<<< orphan*/  port_name; scalar_t__ logout_on_delete; int /*<<< orphan*/ * plogi_link; struct qla_tgt* tgt; } ;
struct TYPE_4__ {scalar_t__ fcport_count; TYPE_1__* hw; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  fcport_waitQ; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 scalar_t__ DSC_DELETED ; 
 scalar_t__ DSC_DELETE_PEND ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ QLA_SESS_DELETED ; 
 scalar_t__ QLA_SESS_DELETION_IN_PROGRESS ; 
 size_t QLT_PLOGI_LINK_CONFLICT ; 
 size_t QLT_PLOGI_LINK_SAME_WWN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,struct fc_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_tgt ; 
 int /*<<< orphan*/  qla24xx_chk_fcp_state (struct fc_port*) ; 
 int /*<<< orphan*/  qla24xx_delete_sess_fn ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void qlt_schedule_sess_for_deletion(struct fc_port *sess)
{
	struct qla_tgt *tgt = sess->tgt;
	unsigned long flags;

	if (sess->disc_state == DSC_DELETE_PEND)
		return;

	if (sess->disc_state == DSC_DELETED) {
		if (tgt && tgt->tgt_stop && (tgt->sess_count == 0))
			wake_up_all(&tgt->waitQ);
		if (sess->vha->fcport_count == 0)
			wake_up_all(&sess->vha->fcport_waitQ);

		if (!sess->plogi_link[QLT_PLOGI_LINK_SAME_WWN] &&
			!sess->plogi_link[QLT_PLOGI_LINK_CONFLICT])
			return;
	}

	if (sess->deleted == QLA_SESS_DELETED)
		sess->logout_on_delete = 0;

	spin_lock_irqsave(&sess->vha->work_lock, flags);
	if (sess->deleted == QLA_SESS_DELETION_IN_PROGRESS) {
		spin_unlock_irqrestore(&sess->vha->work_lock, flags);
		return;
	}
	sess->deleted = QLA_SESS_DELETION_IN_PROGRESS;
	spin_unlock_irqrestore(&sess->vha->work_lock, flags);

	sess->disc_state = DSC_DELETE_PEND;

	qla24xx_chk_fcp_state(sess);

	ql_dbg(ql_dbg_tgt, sess->vha, 0xe001,
	    "Scheduling sess %p for deletion %8phC\n",
	    sess, sess->port_name);

	INIT_WORK(&sess->del_work, qla24xx_delete_sess_fn);
	WARN_ON(!queue_work(sess->vha->hw->wq, &sess->del_work));
}