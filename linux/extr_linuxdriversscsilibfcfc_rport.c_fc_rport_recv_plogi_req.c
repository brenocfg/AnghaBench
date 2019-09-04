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
struct fc_seq_els_data {void* explan; int /*<<< orphan*/  reason; } ;
struct TYPE_3__ {void* port_name; void* node_name; } ;
struct fc_rport_priv {int rp_state; int /*<<< orphan*/  rp_mutex; int /*<<< orphan*/  maxframe_size; TYPE_1__ ids; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;} ;
struct fc_disc {int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {TYPE_2__ tt; int /*<<< orphan*/  mfs; void* wwpn; struct fc_disc disc; int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame {int dummy; } ;
struct fc_els_flogi {int /*<<< orphan*/  fl_wwnn; int /*<<< orphan*/  fl_wwpn; } ;

/* Variables and functions */
 void* ELS_EXPL_INSUF_RES ; 
 void* ELS_EXPL_INV_LEN ; 
 void* ELS_EXPL_NONE ; 
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int /*<<< orphan*/  ELS_LS_RJT ; 
 int /*<<< orphan*/  ELS_RJT_BUSY ; 
 int /*<<< orphan*/  ELS_RJT_INPROG ; 
 int /*<<< orphan*/  ELS_RJT_LOGIC ; 
 int /*<<< orphan*/  ELS_RJT_PROT ; 
 int /*<<< orphan*/  ELS_RJT_UNAB ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REP ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,...) ; 
 int /*<<< orphan*/  FC_RPORT_ID_DBG (struct fc_lport*,int /*<<< orphan*/ ,char*) ; 
#define  RPORT_ST_ADISC 136 
#define  RPORT_ST_DELETE 135 
#define  RPORT_ST_FLOGI 134 
#define  RPORT_ST_INIT 133 
#define  RPORT_ST_PLOGI 132 
#define  RPORT_ST_PLOGI_WAIT 131 
#define  RPORT_ST_PRLI 130 
#define  RPORT_ST_READY 129 
#define  RPORT_ST_RTV 128 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_flogi* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_frame_sid (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_plogi_fill (struct fc_lport*,struct fc_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_plogi_get_maxframe (struct fc_els_flogi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_compatible_roles (struct fc_lport*,struct fc_rport_priv*) ; 
 struct fc_rport_priv* fc_rport_create (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_enter_prli (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_seq_els_rsp_send (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ; 
 void* get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void fc_rport_recv_plogi_req(struct fc_lport *lport,
				    struct fc_frame *rx_fp)
{
	struct fc_disc *disc;
	struct fc_rport_priv *rdata;
	struct fc_frame *fp = rx_fp;
	struct fc_els_flogi *pl;
	struct fc_seq_els_data rjt_data;
	u32 sid;

	lockdep_assert_held(&lport->lp_mutex);

	sid = fc_frame_sid(fp);

	FC_RPORT_ID_DBG(lport, sid, "Received PLOGI request\n");

	pl = fc_frame_payload_get(fp, sizeof(*pl));
	if (!pl) {
		FC_RPORT_ID_DBG(lport, sid, "Received PLOGI too short\n");
		rjt_data.reason = ELS_RJT_PROT;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		goto reject;
	}

	disc = &lport->disc;
	mutex_lock(&disc->disc_mutex);
	rdata = fc_rport_create(lport, sid);
	if (!rdata) {
		mutex_unlock(&disc->disc_mutex);
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		goto reject;
	}

	mutex_lock(&rdata->rp_mutex);
	mutex_unlock(&disc->disc_mutex);

	rdata->ids.port_name = get_unaligned_be64(&pl->fl_wwpn);
	rdata->ids.node_name = get_unaligned_be64(&pl->fl_wwnn);

	/*
	 * If the rport was just created, possibly due to the incoming PLOGI,
	 * set the state appropriately and accept the PLOGI.
	 *
	 * If we had also sent a PLOGI, and if the received PLOGI is from a
	 * higher WWPN, we accept it, otherwise an LS_RJT is sent with reason
	 * "command already in progress".
	 *
	 * XXX TBD: If the session was ready before, the PLOGI should result in
	 * all outstanding exchanges being reset.
	 */
	switch (rdata->rp_state) {
	case RPORT_ST_INIT:
		FC_RPORT_DBG(rdata, "Received PLOGI in INIT state\n");
		break;
	case RPORT_ST_PLOGI_WAIT:
		FC_RPORT_DBG(rdata, "Received PLOGI in PLOGI_WAIT state\n");
		break;
	case RPORT_ST_PLOGI:
		FC_RPORT_DBG(rdata, "Received PLOGI in PLOGI state\n");
		if (rdata->ids.port_name < lport->wwpn) {
			mutex_unlock(&rdata->rp_mutex);
			rjt_data.reason = ELS_RJT_INPROG;
			rjt_data.explan = ELS_EXPL_NONE;
			goto reject;
		}
		break;
	case RPORT_ST_PRLI:
	case RPORT_ST_RTV:
	case RPORT_ST_READY:
	case RPORT_ST_ADISC:
		FC_RPORT_DBG(rdata, "Received PLOGI in logged-in state %d "
			     "- ignored for now\n", rdata->rp_state);
		/* XXX TBD - should reset */
		break;
	case RPORT_ST_FLOGI:
	case RPORT_ST_DELETE:
		FC_RPORT_DBG(rdata, "Received PLOGI in state %s - send busy\n",
			     fc_rport_state(rdata));
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_BUSY;
		rjt_data.explan = ELS_EXPL_NONE;
		goto reject;
	}
	if (!fc_rport_compatible_roles(lport, rdata)) {
		FC_RPORT_DBG(rdata, "Received PLOGI for incompatible role\n");
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_NONE;
		goto reject;
	}

	/*
	 * Get session payload size from incoming PLOGI.
	 */
	rdata->maxframe_size = fc_plogi_get_maxframe(pl, lport->mfs);

	/*
	 * Send LS_ACC.	 If this fails, the originator should retry.
	 */
	fp = fc_frame_alloc(lport, sizeof(*pl));
	if (!fp)
		goto out;

	fc_plogi_fill(lport, fp, ELS_LS_ACC);
	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
	fc_rport_enter_prli(rdata);
out:
	mutex_unlock(&rdata->rp_mutex);
	fc_frame_free(rx_fp);
	return;

reject:
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &rjt_data);
	fc_frame_free(fp);
}