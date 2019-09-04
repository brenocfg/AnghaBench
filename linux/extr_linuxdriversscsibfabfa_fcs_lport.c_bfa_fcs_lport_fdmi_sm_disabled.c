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
struct TYPE_4__ {int pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; TYPE_2__ port_cfg; } ;
struct bfa_fcs_lport_fdmi_s {TYPE_1__* ms; } ;
typedef  enum port_fdmi_event { ____Placeholder_port_fdmi_event } port_fdmi_event ;
struct TYPE_3__ {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_fdmi_sm_disabled(struct bfa_fcs_lport_fdmi_s *fdmi,
			     enum port_fdmi_event event)
{
	struct bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	/* No op State. It can only be enabled at Driver Init. */
}