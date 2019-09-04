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
struct bfa_fcs_lport_fdmi_s {struct bfa_fcs_lport_ms_s* ms; } ;
struct bfa_fcs_lport_ms_s {TYPE_2__* port; struct bfa_fcs_lport_fdmi_s fdmi; } ;
struct TYPE_4__ {TYPE_1__* fcs; } ;
struct TYPE_3__ {scalar_t__ fdmi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_sm_disabled ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_sm_offline ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_lport_fdmi_init(struct bfa_fcs_lport_ms_s *ms)
{
	struct bfa_fcs_lport_fdmi_s *fdmi = &ms->fdmi;

	fdmi->ms = ms;
	if (ms->port->fcs->fdmi_enabled)
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
	else
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_disabled);
}