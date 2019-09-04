#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfi_fcport_req_s {int /*<<< orphan*/  mh; } ;
struct bfa_fcport_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  stats_qfull; int /*<<< orphan*/  stats_reqq_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_REQQ_PORT ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_FCPORT_H2I_STATS_CLEAR_REQ ; 
 int /*<<< orphan*/  BFI_MC_FCPORT ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_fcport_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_reqq_winit (int /*<<< orphan*/ *,void (*) (void*),struct bfa_fcport_s*) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bfi_fcport_req_s*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcport_send_stats_clear(void *cbarg)
{
	struct bfa_fcport_s *fcport = (struct bfa_fcport_s *) cbarg;
	struct bfi_fcport_req_s *msg;

	msg = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);

	if (!msg) {
		fcport->stats_qfull = BFA_TRUE;
		bfa_reqq_winit(&fcport->stats_reqq_wait,
				bfa_fcport_send_stats_clear, fcport);
		bfa_reqq_wait(fcport->bfa, BFA_REQQ_PORT,
						&fcport->stats_reqq_wait);
		return;
	}
	fcport->stats_qfull = BFA_FALSE;

	memset(msg, 0, sizeof(struct bfi_fcport_req_s));
	bfi_h2i_set(msg->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_STATS_CLEAR_REQ,
			bfa_fn_lpu(fcport->bfa));
	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, msg->mh);
}