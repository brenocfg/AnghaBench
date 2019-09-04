#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int dummy; } ;
struct bfa_fcs_itnim_s {TYPE_2__* fcs; int /*<<< orphan*/  bfa_itnim; TYPE_1__* rport; int /*<<< orphan*/  itnim_drv; } ;
typedef  enum bfa_fcs_itnim_event { ____Placeholder_bfa_fcs_itnim_event } bfa_fcs_itnim_event ;
struct TYPE_5__ {scalar_t__ bfad; } ;
struct TYPE_4__ {int pwwn; int /*<<< orphan*/  port; } ;

/* Variables and functions */
#define  BFA_FCS_ITNIM_SM_DELETE 130 
#define  BFA_FCS_ITNIM_SM_HCB_ONLINE 129 
#define  BFA_FCS_ITNIM_SM_OFFLINE 128 
 int /*<<< orphan*/  BFA_ITNIM_AEN_ONLINE ; 
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int BFA_STRING_32 ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_fcb_itnim_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_aen_post (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_free (struct bfa_fcs_itnim_s*) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_hcb_offline ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_online ; 
 int bfa_fcs_lport_get_pwwn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_itnim_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  wwn2str (char*,int) ; 

__attribute__((used)) static void
bfa_fcs_itnim_sm_hcb_online(struct bfa_fcs_itnim_s *itnim,
			    enum bfa_fcs_itnim_event event)
{
	struct bfad_s *bfad = (struct bfad_s *)itnim->fcs->bfad;
	char	lpwwn_buf[BFA_STRING_32];
	char	rpwwn_buf[BFA_STRING_32];

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_HCB_ONLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_online);
		bfa_fcb_itnim_online(itnim->itnim_drv);
		wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(itnim->rport->port));
		wwn2str(rpwwn_buf, itnim->rport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Target (WWN = %s) is online for initiator (WWN = %s)\n",
		rpwwn_buf, lpwwn_buf);
		bfa_fcs_itnim_aen_post(itnim, BFA_ITNIM_AEN_ONLINE);
		break;

	case BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_offline);
		bfa_itnim_offline(itnim->bfa_itnim);
		break;

	case BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcs_itnim_free(itnim);
		break;

	default:
		bfa_sm_fault(itnim->fcs, event);
	}
}