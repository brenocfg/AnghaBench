#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
union bfi_fcport_i2h_msg_u {TYPE_12__* pstatsget_rsp; int /*<<< orphan*/  trunk_scn; TYPE_11__* event; TYPE_5__* penable_rsp; struct bfi_msg_s* msg; } ;
struct TYPE_17__ {int msg_id; } ;
struct bfi_msg_s {TYPE_2__ mhdr; } ;
struct bfa_s {int dummy; } ;
struct TYPE_23__ {int /*<<< orphan*/  qos_bw_op; int /*<<< orphan*/  state; int /*<<< orphan*/  qos_bw; } ;
struct TYPE_22__ {void* state; } ;
struct TYPE_21__ {int /*<<< orphan*/  bb_cr_enabled; int /*<<< orphan*/  qos_bw; int /*<<< orphan*/  qos_enabled; int /*<<< orphan*/  trunked; void* q_depth; void* path_tov; void* maxfrsize; } ;
struct TYPE_18__ {int /*<<< orphan*/  state; } ;
struct TYPE_19__ {TYPE_3__ attr; } ;
struct TYPE_16__ {union bfi_fcport_i2h_msg_u i2hmsg; } ;
struct bfa_fcport_s {int /*<<< orphan*/  stats_status; int /*<<< orphan*/  timer; int /*<<< orphan*/  statsclr_pending_q; int /*<<< orphan*/  stats_pending_q; TYPE_8__ qos_attr; TYPE_7__ bbcr_attr; TYPE_6__ cfg; int /*<<< orphan*/  msgtag; int /*<<< orphan*/  use_flash_cfg; TYPE_4__ trunk; int /*<<< orphan*/  stats_dma_ready; int /*<<< orphan*/  sm; TYPE_1__ event_arg; } ;
struct TYPE_24__ {int /*<<< orphan*/  qos_bw_op; } ;
struct TYPE_20__ {int /*<<< orphan*/  msgtag; TYPE_6__ port_cfg; } ;
struct TYPE_15__ {int /*<<< orphan*/  status; } ;
struct TYPE_13__ {TYPE_9__ qos_attr; int /*<<< orphan*/  linkstate_rsn; int /*<<< orphan*/  linkstate; } ;
struct TYPE_14__ {TYPE_10__ link_state; } ;

/* Variables and functions */
 void* BFA_BBCR_DISABLED ; 
 void* BFA_BBCR_OFFLINE ; 
 int /*<<< orphan*/  BFA_FALSE ; 
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_DISABLE ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_ENABLE ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_FAA_MISCONFIG ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_FWRSP ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_LINKDOWN ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_LINKUP ; 
 int /*<<< orphan*/  BFA_PORT_LINKSTATE_RSN_FAA_MISCONFIG ; 
 int /*<<< orphan*/  BFA_PORT_LINKUP ; 
 int /*<<< orphan*/  BFA_QOS_DISABLED ; 
 int /*<<< orphan*/  BFA_QOS_OFFLINE ; 
 int /*<<< orphan*/  BFA_STATUS_ETIMER ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFA_TRUNK_DISABLED ; 
 int /*<<< orphan*/  BFA_TRUNK_OFFLINE ; 
#define  BFI_FCPORT_I2H_DISABLE_AEN 135 
#define  BFI_FCPORT_I2H_DISABLE_RSP 134 
#define  BFI_FCPORT_I2H_ENABLE_AEN 133 
#define  BFI_FCPORT_I2H_ENABLE_RSP 132 
#define  BFI_FCPORT_I2H_EVENT 131 
#define  BFI_FCPORT_I2H_STATS_CLEAR_RSP 130 
#define  BFI_FCPORT_I2H_STATS_GET_RSP 129 
#define  BFI_FCPORT_I2H_TRUNK_SCN 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __bfa_cb_fcport_stats_clr (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bfa_cb_fcport_stats_get (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int bfa_sm_to_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 
 int /*<<< orphan*/  bfa_trunk_scn (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (void*) ; 
 int /*<<< orphan*/  hal_port_sm_table ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void
bfa_fcport_isr(struct bfa_s *bfa, struct bfi_msg_s *msg)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	union bfi_fcport_i2h_msg_u i2hmsg;

	i2hmsg.msg = msg;
	fcport->event_arg.i2hmsg = i2hmsg;

	bfa_trc(bfa, msg->mhdr.msg_id);
	bfa_trc(bfa, bfa_sm_to_state(hal_port_sm_table, fcport->sm));

	switch (msg->mhdr.msg_id) {
	case BFI_FCPORT_I2H_ENABLE_RSP:
		if (fcport->msgtag == i2hmsg.penable_rsp->msgtag) {

			fcport->stats_dma_ready = BFA_TRUE;
			if (fcport->use_flash_cfg) {
				fcport->cfg = i2hmsg.penable_rsp->port_cfg;
				fcport->cfg.maxfrsize =
					cpu_to_be16(fcport->cfg.maxfrsize);
				fcport->cfg.path_tov =
					cpu_to_be16(fcport->cfg.path_tov);
				fcport->cfg.q_depth =
					cpu_to_be16(fcport->cfg.q_depth);

				if (fcport->cfg.trunked)
					fcport->trunk.attr.state =
						BFA_TRUNK_OFFLINE;
				else
					fcport->trunk.attr.state =
						BFA_TRUNK_DISABLED;
				fcport->qos_attr.qos_bw =
					i2hmsg.penable_rsp->port_cfg.qos_bw;
				fcport->use_flash_cfg = BFA_FALSE;
			}

			if (fcport->cfg.qos_enabled)
				fcport->qos_attr.state = BFA_QOS_OFFLINE;
			else
				fcport->qos_attr.state = BFA_QOS_DISABLED;

			fcport->qos_attr.qos_bw_op =
					i2hmsg.penable_rsp->port_cfg.qos_bw;

			if (fcport->cfg.bb_cr_enabled)
				fcport->bbcr_attr.state = BFA_BBCR_OFFLINE;
			else
				fcport->bbcr_attr.state = BFA_BBCR_DISABLED;

			bfa_sm_send_event(fcport, BFA_FCPORT_SM_FWRSP);
		}
		break;

	case BFI_FCPORT_I2H_DISABLE_RSP:
		if (fcport->msgtag == i2hmsg.penable_rsp->msgtag)
			bfa_sm_send_event(fcport, BFA_FCPORT_SM_FWRSP);
		break;

	case BFI_FCPORT_I2H_EVENT:
		if (fcport->cfg.bb_cr_enabled)
			fcport->bbcr_attr.state = BFA_BBCR_OFFLINE;
		else
			fcport->bbcr_attr.state = BFA_BBCR_DISABLED;

		if (i2hmsg.event->link_state.linkstate == BFA_PORT_LINKUP)
			bfa_sm_send_event(fcport, BFA_FCPORT_SM_LINKUP);
		else {
			if (i2hmsg.event->link_state.linkstate_rsn ==
			    BFA_PORT_LINKSTATE_RSN_FAA_MISCONFIG)
				bfa_sm_send_event(fcport,
						  BFA_FCPORT_SM_FAA_MISCONFIG);
			else
				bfa_sm_send_event(fcport,
						  BFA_FCPORT_SM_LINKDOWN);
		}
		fcport->qos_attr.qos_bw_op =
				i2hmsg.event->link_state.qos_attr.qos_bw_op;
		break;

	case BFI_FCPORT_I2H_TRUNK_SCN:
		bfa_trunk_scn(fcport, i2hmsg.trunk_scn);
		break;

	case BFI_FCPORT_I2H_STATS_GET_RSP:
		/*
		 * check for timer pop before processing the rsp
		 */
		if (list_empty(&fcport->stats_pending_q) ||
		    (fcport->stats_status == BFA_STATUS_ETIMER))
			break;

		bfa_timer_stop(&fcport->timer);
		fcport->stats_status = i2hmsg.pstatsget_rsp->status;
		__bfa_cb_fcport_stats_get(fcport, BFA_TRUE);
		break;

	case BFI_FCPORT_I2H_STATS_CLEAR_RSP:
		/*
		 * check for timer pop before processing the rsp
		 */
		if (list_empty(&fcport->statsclr_pending_q) ||
		    (fcport->stats_status == BFA_STATUS_ETIMER))
			break;

		bfa_timer_stop(&fcport->timer);
		fcport->stats_status = BFA_STATUS_OK;
		__bfa_cb_fcport_stats_clr(fcport, BFA_TRUE);
		break;

	case BFI_FCPORT_I2H_ENABLE_AEN:
		bfa_sm_send_event(fcport, BFA_FCPORT_SM_ENABLE);
		break;

	case BFI_FCPORT_I2H_DISABLE_AEN:
		bfa_sm_send_event(fcport, BFA_FCPORT_SM_DISABLE);
		break;

	default:
		WARN_ON(1);
	break;
	}
}