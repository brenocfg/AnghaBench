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
struct TYPE_4__ {scalar_t__ rpsc_speed; } ;
struct bfa_fcs_rport_s {TYPE_2__ rpf; TYPE_1__* port; int /*<<< orphan*/  pid; int /*<<< orphan*/  fcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPFSM_EVENT_RPORT_OFFLINE ; 
 scalar_t__ __fcs_min_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_fcs_rpf_rport_offline(struct bfa_fcs_rport_s *rport)
{
	bfa_trc(rport->fcs, rport->pid);

	if (__fcs_min_cfg(rport->port->fcs))
		return;

	rport->rpf.rpsc_speed = 0;
	bfa_sm_send_event(&rport->rpf, RPFSM_EVENT_RPORT_OFFLINE);
}