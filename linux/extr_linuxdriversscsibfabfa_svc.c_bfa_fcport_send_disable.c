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
struct bfi_fcport_req_s {int /*<<< orphan*/  mh; scalar_t__ msgtag; } ;
struct bfa_fcport_s {int /*<<< orphan*/  bfa; scalar_t__ msgtag; int /*<<< orphan*/  reqq_wait; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_REQQ_PORT ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_FCPORT_H2I_DISABLE_REQ ; 
 int /*<<< orphan*/  BFI_MC_FCPORT ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_fcport_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	bfa_boolean_t
bfa_fcport_send_disable(struct bfa_fcport_s *fcport)
{
	struct bfi_fcport_req_s *m;

	/*
	 * Increment message tag before queue check, so that responses to old
	 * requests are discarded.
	 */
	fcport->msgtag++;

	/*
	 * check for room in queue to send request now
	 */
	m = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);
	if (!m) {
		bfa_reqq_wait(fcport->bfa, BFA_REQQ_PORT,
							&fcport->reqq_wait);
		return BFA_FALSE;
	}

	bfi_h2i_set(m->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_DISABLE_REQ,
			bfa_fn_lpu(fcport->bfa));
	m->msgtag = fcport->msgtag;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, m->mh);

	return BFA_TRUE;
}