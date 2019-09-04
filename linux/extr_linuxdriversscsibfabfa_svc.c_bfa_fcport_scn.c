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
struct TYPE_2__ {scalar_t__ trunked; } ;
struct bfa_fcport_s {int /*<<< orphan*/  ln; TYPE_1__ cfg; } ;
typedef  enum bfa_port_linkstate { ____Placeholder_bfa_port_linkstate } bfa_port_linkstate ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCPORT_LN_SM_LINKDOWN ; 
 int /*<<< orphan*/  BFA_FCPORT_LN_SM_LINKUP ; 
#define  BFA_PORT_LINKDOWN 129 
#define  BFA_PORT_LINKUP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcport_scn(struct bfa_fcport_s *fcport, enum bfa_port_linkstate event,
	bfa_boolean_t trunk)
{
	if (fcport->cfg.trunked && !trunk)
		return;

	switch (event) {
	case BFA_PORT_LINKUP:
		bfa_sm_send_event(&fcport->ln, BFA_FCPORT_LN_SM_LINKUP);
		break;
	case BFA_PORT_LINKDOWN:
		bfa_sm_send_event(&fcport->ln, BFA_FCPORT_LN_SM_LINKDOWN);
		break;
	default:
		WARN_ON(1);
	}
}