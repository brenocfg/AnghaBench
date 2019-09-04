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
typedef  scalar_t__ u16 ;
struct fchs_s {int dummy; } ;
struct fc_rpsc2_acc_s {scalar_t__ els_cmd; scalar_t__ num_pids; TYPE_1__* port_info; } ;
struct fc_ls_rjt_s {scalar_t__ reason_code; scalar_t__ reason_code_expl; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rpsc_rejects; int /*<<< orphan*/  rpsc_accs; int /*<<< orphan*/  rpsc_failed; } ;
struct bfa_fcs_rport_s {TYPE_2__ stats; int /*<<< orphan*/  fcs; int /*<<< orphan*/  pid; } ;
struct bfa_fcs_rpf_s {int /*<<< orphan*/  rpsc_speed; struct bfa_fcs_rport_s* rport; } ;
typedef  scalar_t__ bfa_status_t ;
struct TYPE_3__ {scalar_t__ speed; scalar_t__ index; scalar_t__ type; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 scalar_t__ BFA_FCXP_RSP_PLD (struct bfa_fcxp_s*) ; 
 scalar_t__ BFA_STATUS_ETIMER ; 
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ FC_ELS_ACC ; 
 scalar_t__ FC_LS_RJT_RSN_CMD_NOT_SUPP ; 
 int /*<<< orphan*/  RPFSM_EVENT_RPSC_COMP ; 
 int /*<<< orphan*/  RPFSM_EVENT_RPSC_ERROR ; 
 int /*<<< orphan*/  RPFSM_EVENT_RPSC_FAIL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_ntoh3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fc_rpsc_operspeed_to_bfa_speed (scalar_t__) ; 

__attribute__((used)) static void
bfa_fcs_rpf_rpsc2_response(void *fcsarg, struct bfa_fcxp_s *fcxp, void *cbarg,
			    bfa_status_t req_status, u32 rsp_len,
			    u32 resid_len, struct fchs_s *rsp_fchs)
{
	struct bfa_fcs_rpf_s *rpf = (struct bfa_fcs_rpf_s *) cbarg;
	struct bfa_fcs_rport_s *rport = rpf->rport;
	struct fc_ls_rjt_s *ls_rjt;
	struct fc_rpsc2_acc_s *rpsc2_acc;
	u16	num_ents;

	bfa_trc(rport->fcs, req_status);

	if (req_status != BFA_STATUS_OK) {
		bfa_trc(rport->fcs, req_status);
		if (req_status == BFA_STATUS_ETIMER)
			rport->stats.rpsc_failed++;
		bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_ERROR);
		return;
	}

	rpsc2_acc = (struct fc_rpsc2_acc_s *) BFA_FCXP_RSP_PLD(fcxp);
	if (rpsc2_acc->els_cmd == FC_ELS_ACC) {
		rport->stats.rpsc_accs++;
		num_ents = be16_to_cpu(rpsc2_acc->num_pids);
		bfa_trc(rport->fcs, num_ents);
		if (num_ents > 0) {
			WARN_ON(be32_to_cpu(rpsc2_acc->port_info[0].pid) !=
						bfa_ntoh3b(rport->pid));
			bfa_trc(rport->fcs,
				be32_to_cpu(rpsc2_acc->port_info[0].pid));
			bfa_trc(rport->fcs,
				be16_to_cpu(rpsc2_acc->port_info[0].speed));
			bfa_trc(rport->fcs,
				be16_to_cpu(rpsc2_acc->port_info[0].index));
			bfa_trc(rport->fcs,
				rpsc2_acc->port_info[0].type);

			if (rpsc2_acc->port_info[0].speed == 0) {
				bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_ERROR);
				return;
			}

			rpf->rpsc_speed = fc_rpsc_operspeed_to_bfa_speed(
				be16_to_cpu(rpsc2_acc->port_info[0].speed));

			bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_COMP);
		}
	} else {
		ls_rjt = (struct fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);
		bfa_trc(rport->fcs, ls_rjt->reason_code);
		bfa_trc(rport->fcs, ls_rjt->reason_code_expl);
		rport->stats.rpsc_rejects++;
		if (ls_rjt->reason_code == FC_LS_RJT_RSN_CMD_NOT_SUPP)
			bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_FAIL);
		else
			bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_ERROR);
	}
}