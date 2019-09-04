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
struct bfa_fcport_s {int /*<<< orphan*/  stats_status; scalar_t__ stats_qfull; int /*<<< orphan*/  stats_reqq_wait; int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 int /*<<< orphan*/  BFA_STATUS_ETIMER ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  __bfa_cb_fcport_stats_get (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wcancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
bfa_fcport_stats_get_timeout(void *cbarg)
{
	struct bfa_fcport_s *fcport = (struct bfa_fcport_s *) cbarg;

	bfa_trc(fcport->bfa, fcport->stats_qfull);

	if (fcport->stats_qfull) {
		bfa_reqq_wcancel(&fcport->stats_reqq_wait);
		fcport->stats_qfull = BFA_FALSE;
	}

	fcport->stats_status = BFA_STATUS_ETIMER;
	__bfa_cb_fcport_stats_get(fcport, BFA_TRUE);
}