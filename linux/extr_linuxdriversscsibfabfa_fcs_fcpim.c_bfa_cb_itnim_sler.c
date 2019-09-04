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
struct TYPE_3__ {int /*<<< orphan*/  sler; } ;
struct bfa_fcs_itnim_s {TYPE_2__* rport; int /*<<< orphan*/  fcs; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPSM_EVENT_LOGO_IMP ; 
 int /*<<< orphan*/  bfa_sm_send_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_cb_itnim_sler(void *cb_arg)
{
	struct bfa_fcs_itnim_s *itnim = (struct bfa_fcs_itnim_s *) cb_arg;

	itnim->stats.sler++;
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_sm_send_event(itnim->rport, RPSM_EVENT_LOGO_IMP);
}