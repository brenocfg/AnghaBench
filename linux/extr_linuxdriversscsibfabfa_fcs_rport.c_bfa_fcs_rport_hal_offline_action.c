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
struct bfad_s {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  offlines; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  pid; int /*<<< orphan*/  itnim; struct bfa_fcs_lport_s* port; int /*<<< orphan*/  pwwn; TYPE_2__ stats; int /*<<< orphan*/  bfa_rport; } ;
struct bfa_fcs_lport_s {TYPE_1__* fcs; } ;
struct TYPE_3__ {scalar_t__ bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_PID_IS_WKA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  BFA_RPORT_AEN_DISCONNECT ; 
 int /*<<< orphan*/  BFA_RPORT_AEN_OFFLINE ; 
 int BFA_STRING_32 ; 
 scalar_t__ BFA_TRUE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_fcs_itnim_rport_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_pwwn (struct bfa_fcs_lport_s*) ; 
 scalar_t__ bfa_fcs_lport_is_initiator (struct bfa_fcs_lport_s*) ; 
 scalar_t__ bfa_fcs_lport_is_online (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rpf_rport_offline (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_aen_post (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rport_fcs_offline_action (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  wwn2str (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_hal_offline_action(struct bfa_fcs_rport_s *rport)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct bfad_s *bfad = (struct bfad_s *)port->fcs->bfad;
	char	lpwwn_buf[BFA_STRING_32];
	char	rpwwn_buf[BFA_STRING_32];

	if (!rport->bfa_rport) {
		bfa_fcs_rport_fcs_offline_action(rport);
		return;
	}

	rport->stats.offlines++;

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	wwn2str(rpwwn_buf, rport->pwwn);
	if (!BFA_FCS_PID_IS_WKA(rport->pid)) {
		if (bfa_fcs_lport_is_online(rport->port) == BFA_TRUE) {
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Remote port (WWN = %s) connectivity lost for "
				"logical port (WWN = %s)\n",
				rpwwn_buf, lpwwn_buf);
			bfa_fcs_rport_aen_post(rport,
				BFA_RPORT_AEN_DISCONNECT, NULL);
		} else {
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Remote port (WWN = %s) offlined by "
				"logical port (WWN = %s)\n",
				rpwwn_buf, lpwwn_buf);
			bfa_fcs_rport_aen_post(rport,
				BFA_RPORT_AEN_OFFLINE, NULL);
		}
	}

	if (bfa_fcs_lport_is_initiator(port)) {
		bfa_fcs_itnim_rport_offline(rport->itnim);
		if (!BFA_FCS_PID_IS_WKA(rport->pid))
			bfa_fcs_rpf_rport_offline(rport);
	}
}