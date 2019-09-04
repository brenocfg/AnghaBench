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
struct fcoe_port {struct bnx2fc_interface* priv; } ;
struct TYPE_4__ {int roles; } ;
struct fc_rport_priv {int flags; TYPE_1__ ids; struct fc_rport* rport; } ;
struct fc_rport {int dummy; } ;
struct TYPE_6__ {int header; } ;
struct b577xx_fcoe_rx_doorbell {int params; TYPE_3__ hdr; } ;
struct TYPE_5__ {int header; } ;
struct b577xx_doorbell_set_prod {TYPE_2__ header; } ;
struct bnx2fc_rport {int fcoe_conn_id; int sq_curr_toggle_bit; int cq_curr_toggle_bit; int rq_prod_idx; int /*<<< orphan*/  upld_wait; int /*<<< orphan*/  ofld_wait; int /*<<< orphan*/  active_tm_queue; int /*<<< orphan*/  els_queue; int /*<<< orphan*/  io_retire_queue; int /*<<< orphan*/  active_cmd_queue; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  tgt_lock; scalar_t__ io_timeout; int /*<<< orphan*/  dev_type; scalar_t__ retry_delay_timestamp; int /*<<< orphan*/  num_active_ios; scalar_t__ rq_cons_idx; scalar_t__ cq_cons_idx; scalar_t__ sq_prod_idx; int /*<<< orphan*/  free_sqes; int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  max_rqes; int /*<<< orphan*/  max_sqes; struct fcoe_port* port; struct fc_rport_priv* rdata; struct fc_rport* rport; struct b577xx_fcoe_rx_doorbell rx_db; struct b577xx_doorbell_set_prod sq_db; } ;
struct bnx2fc_interface {struct bnx2fc_hba* hba; } ;
struct bnx2fc_hba {scalar_t__ num_ofld_sess; } ;

/* Variables and functions */
 int B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT ; 
 int B577XX_DOORBELL_HDR_DB_TYPE ; 
 int B577XX_DOORBELL_HDR_DB_TYPE_SHIFT ; 
 int B577XX_DOORBELL_HDR_RX_SHIFT ; 
 int B577XX_FCOE_CONNECTION_TYPE ; 
 int B577XX_FCOE_RX_DOORBELL_NEGATIVE_ARM_SHIFT ; 
 int B577XX_FCOE_RX_DOORBELL_OPCODE_SHIFT ; 
 int /*<<< orphan*/  BNX2FC_CQ_WQES_MAX ; 
 scalar_t__ BNX2FC_IO_TIMEOUT ; 
 scalar_t__ BNX2FC_NUM_MAX_SESS ; 
 int /*<<< orphan*/  BNX2FC_RQ_WQES_MAX ; 
 int /*<<< orphan*/  BNX2FC_SQ_WQES_MAX ; 
 int /*<<< orphan*/  BNX2FC_TGT_DBG (struct bnx2fc_rport*,char*,...) ; 
 int FC_RPORT_ROLE_FCP_INITIATOR ; 
 int FC_RPORT_ROLE_FCP_TARGET ; 
 int FC_RP_FLAGS_RETRY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_DISK ; 
 int /*<<< orphan*/  TYPE_TAPE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bnx2fc_alloc_conn_id (struct bnx2fc_hba*,struct bnx2fc_rport*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2fc_init_tgt(struct bnx2fc_rport *tgt,
			   struct fcoe_port *port,
			   struct fc_rport_priv *rdata)
{

	struct fc_rport *rport = rdata->rport;
	struct bnx2fc_interface *interface = port->priv;
	struct bnx2fc_hba *hba = interface->hba;
	struct b577xx_doorbell_set_prod *sq_db = &tgt->sq_db;
	struct b577xx_fcoe_rx_doorbell *rx_db = &tgt->rx_db;

	tgt->rport = rport;
	tgt->rdata = rdata;
	tgt->port = port;

	if (hba->num_ofld_sess >= BNX2FC_NUM_MAX_SESS) {
		BNX2FC_TGT_DBG(tgt, "exceeded max sessions. logoff this tgt\n");
		tgt->fcoe_conn_id = -1;
		return -1;
	}

	tgt->fcoe_conn_id = bnx2fc_alloc_conn_id(hba, tgt);
	if (tgt->fcoe_conn_id == -1)
		return -1;

	BNX2FC_TGT_DBG(tgt, "init_tgt - conn_id = 0x%x\n", tgt->fcoe_conn_id);

	tgt->max_sqes = BNX2FC_SQ_WQES_MAX;
	tgt->max_rqes = BNX2FC_RQ_WQES_MAX;
	tgt->max_cqes = BNX2FC_CQ_WQES_MAX;
	atomic_set(&tgt->free_sqes, BNX2FC_SQ_WQES_MAX);

	/* Initialize the toggle bit */
	tgt->sq_curr_toggle_bit = 1;
	tgt->cq_curr_toggle_bit = 1;
	tgt->sq_prod_idx = 0;
	tgt->cq_cons_idx = 0;
	tgt->rq_prod_idx = 0x8000;
	tgt->rq_cons_idx = 0;
	atomic_set(&tgt->num_active_ios, 0);
	tgt->retry_delay_timestamp = 0;

	if (rdata->flags & FC_RP_FLAGS_RETRY &&
	    rdata->ids.roles & FC_RPORT_ROLE_FCP_TARGET &&
	    !(rdata->ids.roles & FC_RPORT_ROLE_FCP_INITIATOR)) {
		tgt->dev_type = TYPE_TAPE;
		tgt->io_timeout = 0; /* use default ULP timeout */
	} else {
		tgt->dev_type = TYPE_DISK;
		tgt->io_timeout = BNX2FC_IO_TIMEOUT;
	}

	/* initialize sq doorbell */
	sq_db->header.header = B577XX_DOORBELL_HDR_DB_TYPE;
	sq_db->header.header |= B577XX_FCOE_CONNECTION_TYPE <<
					B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT;
	/* initialize rx doorbell */
	rx_db->hdr.header = ((0x1 << B577XX_DOORBELL_HDR_RX_SHIFT) |
			  (0x1 << B577XX_DOORBELL_HDR_DB_TYPE_SHIFT) |
			  (B577XX_FCOE_CONNECTION_TYPE <<
				B577XX_DOORBELL_HDR_CONN_TYPE_SHIFT));
	rx_db->params = (0x2 << B577XX_FCOE_RX_DOORBELL_NEGATIVE_ARM_SHIFT) |
		     (0x3 << B577XX_FCOE_RX_DOORBELL_OPCODE_SHIFT);

	spin_lock_init(&tgt->tgt_lock);
	spin_lock_init(&tgt->cq_lock);

	/* Initialize active_cmd_queue list */
	INIT_LIST_HEAD(&tgt->active_cmd_queue);

	/* Initialize IO retire queue */
	INIT_LIST_HEAD(&tgt->io_retire_queue);

	INIT_LIST_HEAD(&tgt->els_queue);

	/* Initialize active_tm_queue list */
	INIT_LIST_HEAD(&tgt->active_tm_queue);

	init_waitqueue_head(&tgt->ofld_wait);
	init_waitqueue_head(&tgt->upld_wait);

	return 0;
}