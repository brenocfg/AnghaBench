#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ns_gidft_sent; int /*<<< orphan*/  ns_gidft_alloc_wait; } ;
struct bfa_fcs_lport_s {TYPE_2__ stats; TYPE_3__* fcs; int /*<<< orphan*/  lp_tag; TYPE_1__* fabric; int /*<<< orphan*/  pid; } ;
struct bfa_fcs_lport_ns_s {struct bfa_fcs_lport_s* port; struct bfa_fcxp_s* fcxp; int /*<<< orphan*/  fcxp_wqe; } ;
struct TYPE_7__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_5__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_FCCT_TOV ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  NSSM_EVENT_GIDFT_SENT ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fcxp_alloc_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (void*,struct bfa_fcxp_s*),struct bfa_fcs_lport_ns_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ns_gid_ft_response ; 
 int /*<<< orphan*/  bfa_fcxp_get_maxrsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_ns_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int fc_gid_ft_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_ns_send_gid_ft(void *ns_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_lport_ns_s *ns = ns_cbarg;
	struct bfa_fcs_lport_s *port = ns->port;
	struct fchs_s fchs;
	int             len;
	struct bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		port->stats.ns_gidft_alloc_wait++;
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_gid_ft, ns, BFA_TRUE);
		return;
	}
	ns->fcxp = fcxp;

	/*
	 * This query is only initiated for FCP initiator mode.
	 */
	len = fc_gid_ft_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			      ns->port->pid, FC_TYPE_FCP);

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_gid_ft_response, (void *)ns,
			  bfa_fcxp_get_maxrsp(port->fcs->bfa), FC_FCCT_TOV);

	port->stats.ns_gidft_sent++;

	bfa_sm_send_event(ns, NSSM_EVENT_GIDFT_SENT);
}