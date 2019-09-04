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
struct bfa_fcs_rpf_s {struct bfa_fcs_rport_s* rport; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  pid; int /*<<< orphan*/  fcs; struct bfa_fcs_rpf_s rpf; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcs_rpf_sm_uninit ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_fcs_rpf_init(struct bfa_fcs_rport_s *rport)
{
	struct bfa_fcs_rpf_s *rpf = &rport->rpf;

	bfa_trc(rport->fcs, rport->pid);
	rpf->rport = rport;

	bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_uninit);
}