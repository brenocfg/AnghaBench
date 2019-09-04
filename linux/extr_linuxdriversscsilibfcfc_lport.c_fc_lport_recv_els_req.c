#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* disc_recv_req ) (struct fc_lport*,struct fc_frame*) ;} ;
struct fc_lport {int /*<<< orphan*/  lp_mutex; TYPE_1__ tt; int /*<<< orphan*/  point_to_multipoint; int /*<<< orphan*/  link_up; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
#define  ELS_ECHO 133 
#define  ELS_FLOGI 132 
#define  ELS_LOGO 131 
#define  ELS_RLIR 130 
#define  ELS_RNID 129 
#define  ELS_RSCN 128 
 int /*<<< orphan*/  FC_FID_FLOGI ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_sid (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_recv_echo_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_recv_flogi_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_recv_logo_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_recv_rlir_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_recv_rnid_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void fc_lport_recv_els_req(struct fc_lport *lport,
				  struct fc_frame *fp)
{
	mutex_lock(&lport->lp_mutex);

	/*
	 * Handle special ELS cases like FLOGI, LOGO, and
	 * RSCN here.  These don't require a session.
	 * Even if we had a session, it might not be ready.
	 */
	if (!lport->link_up)
		fc_frame_free(fp);
	else {
		/*
		 * Check opcode.
		 */
		switch (fc_frame_payload_op(fp)) {
		case ELS_FLOGI:
			if (!lport->point_to_multipoint)
				fc_lport_recv_flogi_req(lport, fp);
			else
				fc_rport_recv_req(lport, fp);
			break;
		case ELS_LOGO:
			if (fc_frame_sid(fp) == FC_FID_FLOGI)
				fc_lport_recv_logo_req(lport, fp);
			else
				fc_rport_recv_req(lport, fp);
			break;
		case ELS_RSCN:
			lport->tt.disc_recv_req(lport, fp);
			break;
		case ELS_ECHO:
			fc_lport_recv_echo_req(lport, fp);
			break;
		case ELS_RLIR:
			fc_lport_recv_rlir_req(lport, fp);
			break;
		case ELS_RNID:
			fc_lport_recv_rnid_req(lport, fp);
			break;
		default:
			fc_rport_recv_req(lport, fp);
			break;
		}
	}
	mutex_unlock(&lport->lp_mutex);
}