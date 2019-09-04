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
struct TYPE_4__ {int /*<<< orphan*/  bb_rcv_sz; } ;
struct TYPE_5__ {int /*<<< orphan*/ * class3_parms; int /*<<< orphan*/ * class2_parms; int /*<<< orphan*/ * class1_parms; TYPE_1__ common; } ;
struct ibmvfc_target {scalar_t__ action; TYPE_2__ service_parms; int /*<<< orphan*/  target_id; struct fc_rport* rport; int /*<<< orphan*/  kref; int /*<<< orphan*/  timer; int /*<<< orphan*/  queue; int /*<<< orphan*/  ids; struct ibmvfc_host* vhost; } ;
struct ibmvfc_host {TYPE_3__* host; } ;
struct fc_rport {int maxframe_size; scalar_t__ rqst_q; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  scsi_target_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_COS_CLASS1 ; 
 int /*<<< orphan*/  FC_COS_CLASS2 ; 
 int /*<<< orphan*/  FC_COS_CLASS3 ; 
 scalar_t__ IBMVFC_TGT_ACTION_DELETED_RPORT ; 
 scalar_t__ IBMVFC_TGT_ACTION_DEL_RPORT ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segments (scalar_t__,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct fc_rport* fc_remote_port_add (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_remote_port_delete (struct fc_rport*) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,scalar_t__) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 

__attribute__((used)) static void ibmvfc_tgt_add_rport(struct ibmvfc_target *tgt)
{
	struct ibmvfc_host *vhost = tgt->vhost;
	struct fc_rport *rport;
	unsigned long flags;

	tgt_dbg(tgt, "Adding rport\n");
	rport = fc_remote_port_add(vhost->host, 0, &tgt->ids);
	spin_lock_irqsave(vhost->host->host_lock, flags);

	if (rport && tgt->action == IBMVFC_TGT_ACTION_DEL_RPORT) {
		tgt_dbg(tgt, "Deleting rport\n");
		list_del(&tgt->queue);
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DELETED_RPORT);
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		fc_remote_port_delete(rport);
		del_timer_sync(&tgt->timer);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
		return;
	} else if (rport && tgt->action == IBMVFC_TGT_ACTION_DELETED_RPORT) {
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		return;
	}

	if (rport) {
		tgt_dbg(tgt, "rport add succeeded\n");
		tgt->rport = rport;
		rport->maxframe_size = be16_to_cpu(tgt->service_parms.common.bb_rcv_sz) & 0x0fff;
		rport->supported_classes = 0;
		tgt->target_id = rport->scsi_target_id;
		if (be32_to_cpu(tgt->service_parms.class1_parms[0]) & 0x80000000)
			rport->supported_classes |= FC_COS_CLASS1;
		if (be32_to_cpu(tgt->service_parms.class2_parms[0]) & 0x80000000)
			rport->supported_classes |= FC_COS_CLASS2;
		if (be32_to_cpu(tgt->service_parms.class3_parms[0]) & 0x80000000)
			rport->supported_classes |= FC_COS_CLASS3;
		if (rport->rqst_q)
			blk_queue_max_segments(rport->rqst_q, 1);
	} else
		tgt_dbg(tgt, "rport add failed\n");
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
}