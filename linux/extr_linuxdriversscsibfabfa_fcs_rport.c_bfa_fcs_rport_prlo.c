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
struct bfa_fcs_rport_s {int /*<<< orphan*/  reply_oxid; int /*<<< orphan*/  prlo; int /*<<< orphan*/  pid; int /*<<< orphan*/  fcs; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  RPSM_EVENT_PRLO_RCVD ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_fcs_rport_prlo(struct bfa_fcs_rport_s *rport, __be16 ox_id)
{
	bfa_trc(rport->fcs, rport->pid);

	rport->prlo = BFA_TRUE;
	rport->reply_oxid = ox_id;
	bfa_sm_send_event(rport, RPSM_EVENT_PRLO_RCVD);
}