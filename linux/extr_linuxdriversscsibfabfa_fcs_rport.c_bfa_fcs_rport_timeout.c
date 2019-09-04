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
struct TYPE_2__ {int /*<<< orphan*/  plogi_timeouts; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  port; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPSM_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rport_plogi_timeouts ; 

__attribute__((used)) static void
bfa_fcs_rport_timeout(void *arg)
{
	struct bfa_fcs_rport_s *rport = (struct bfa_fcs_rport_s *) arg;

	rport->stats.plogi_timeouts++;
	bfa_stats(rport->port, rport_plogi_timeouts);
	bfa_sm_send_event(rport, RPSM_EVENT_TIMEOUT);
}