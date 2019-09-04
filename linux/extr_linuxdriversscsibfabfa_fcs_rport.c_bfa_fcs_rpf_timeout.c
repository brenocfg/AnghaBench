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
struct bfa_fcs_rport_s {int /*<<< orphan*/  pid; int /*<<< orphan*/  fcs; } ;
struct bfa_fcs_rpf_s {struct bfa_fcs_rport_s* rport; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPFSM_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rpf_timeout(void *arg)
{
	struct bfa_fcs_rpf_s *rpf = (struct bfa_fcs_rpf_s *) arg;
	struct bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pid);
	bfa_sm_send_event(rpf, RPFSM_EVENT_TIMEOUT);
}