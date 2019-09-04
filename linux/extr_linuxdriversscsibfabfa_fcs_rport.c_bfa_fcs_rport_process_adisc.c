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
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  s_id; int /*<<< orphan*/  d_id; } ;
struct fc_adisc_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  adisc_rejected; int /*<<< orphan*/  adisc_rcvd; } ;
struct bfa_fcs_rport_s {TYPE_3__ stats; int /*<<< orphan*/  itnim; struct bfa_fcs_lport_s* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_2__* fabric; TYPE_1__ port_cfg; int /*<<< orphan*/  fcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_LS_RJT_EXP_LOGIN_REQUIRED ; 
 int /*<<< orphan*/  FC_LS_RJT_RSN_UNABLE_TO_PERF_CMD ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_fcs_itnim_get_online_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_ls_rjt (struct bfa_fcs_rport_s*,struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fchs_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_adisc_acc_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_process_adisc(struct bfa_fcs_rport_s *rport,
			struct fchs_s *rx_fchs, u16 len)
{
	struct bfa_fcxp_s *fcxp;
	struct fchs_s	fchs;
	struct bfa_fcs_lport_s *port = rport->port;
	struct fc_adisc_s	*adisc;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	rport->stats.adisc_rcvd++;

	adisc = (struct fc_adisc_s *) (rx_fchs + 1);

	/*
	 * Accept if the itnim for this rport is online.
	 * Else reject the ADISC.
	 */
	if (bfa_fcs_itnim_get_online_state(rport->itnim) == BFA_STATUS_OK) {

		fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
		if (!fcxp)
			return;

		len = fc_adisc_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			 rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
			 rx_fchs->ox_id, port->port_cfg.pwwn,
			 port->port_cfg.nwwn);

		bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag,
				BFA_FALSE, FC_CLASS_3, len, &fchs, NULL, NULL,
				FC_MAX_PDUSZ, 0);
	} else {
		rport->stats.adisc_rejected++;
		bfa_fcs_rport_send_ls_rjt(rport, rx_fchs,
					  FC_LS_RJT_RSN_UNABLE_TO_PERF_CMD,
					  FC_LS_RJT_EXP_LOGIN_REQUIRED);
	}
}