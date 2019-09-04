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
struct bfa_fcs_lport_n2n_s {scalar_t__ reply_oxid; scalar_t__ rem_port_wwn; } ;
struct TYPE_2__ {struct bfa_fcs_lport_n2n_s pn2n; } ;
struct bfa_fcs_lport_s {scalar_t__ pid; int /*<<< orphan*/  fcs; TYPE_1__ port_topo; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
bfa_fcs_lport_n2n_offline(struct bfa_fcs_lport_s *port)
{
	struct bfa_fcs_lport_n2n_s *n2n_port = &port->port_topo.pn2n;

	bfa_trc(port->fcs, port->pid);
	port->pid = 0;
	n2n_port->rem_port_wwn = 0;
	n2n_port->reply_oxid = 0;
}