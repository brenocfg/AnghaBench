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
typedef  int u32 ;
struct fchs_s {int dummy; } ;
struct fc_ls_rjt_s {int reason_code; int reason_code_expl; } ;
struct fc_logi_s {int dummy; } ;
struct fc_els_cmd_s {int els_code; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ns_plogi_unknown_rsp; int /*<<< orphan*/  ns_rejects; int /*<<< orphan*/  ns_plogi_accepts; int /*<<< orphan*/  ns_plogi_acc_err; int /*<<< orphan*/  ns_plogi_rsp_err; } ;
struct TYPE_3__ {int pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; TYPE_2__ stats; TYPE_1__ port_cfg; } ;
struct bfa_fcs_lport_ns_s {struct bfa_fcs_lport_s* port; } ;
typedef  int bfa_status_t ;

/* Variables and functions */
 scalar_t__ BFA_FCXP_RSP_PLD (struct bfa_fcxp_s*) ; 
 int BFA_STATUS_OK ; 
#define  FC_ELS_ACC 129 
#define  FC_ELS_LS_RJT 128 
 int /*<<< orphan*/  NSSM_EVENT_RSP_ERROR ; 
 int /*<<< orphan*/  NSSM_EVENT_RSP_OK ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_ns_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_ns_plogi_response(void *fcsarg, struct bfa_fcxp_s *fcxp,
			void *cbarg, bfa_status_t req_status, u32 rsp_len,
		       u32 resid_len, struct fchs_s *rsp_fchs)
{
	struct bfa_fcs_lport_ns_s *ns = (struct bfa_fcs_lport_ns_s *) cbarg;
	struct bfa_fcs_lport_s *port = ns->port;
	/* struct fc_logi_s *plogi_resp; */
	struct fc_els_cmd_s *els_cmd;
	struct fc_ls_rjt_s *ls_rjt;

	bfa_trc(port->fcs, req_status);
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	if (req_status != BFA_STATUS_OK) {
		bfa_trc(port->fcs, req_status);
		port->stats.ns_plogi_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		return;
	}

	els_cmd = (struct fc_els_cmd_s *) BFA_FCXP_RSP_PLD(fcxp);

	switch (els_cmd->els_code) {

	case FC_ELS_ACC:
		if (rsp_len < sizeof(struct fc_logi_s)) {
			bfa_trc(port->fcs, rsp_len);
			port->stats.ns_plogi_acc_err++;
			bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
			break;
		}
		port->stats.ns_plogi_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		break;

	case FC_ELS_LS_RJT:
		ls_rjt = (struct fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);

		bfa_trc(port->fcs, ls_rjt->reason_code);
		bfa_trc(port->fcs, ls_rjt->reason_code_expl);

		port->stats.ns_rejects++;

		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		break;

	default:
		port->stats.ns_plogi_unknown_rsp++;
		bfa_trc(port->fcs, els_cmd->els_code);
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
	}
}