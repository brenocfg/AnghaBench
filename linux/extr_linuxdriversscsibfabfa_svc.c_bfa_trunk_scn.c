#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfi_fcport_trunk_scn_s {scalar_t__ trunk_state; scalar_t__ trunk_speed; struct bfi_fcport_trunk_link_s* tlink; } ;
struct bfi_fcport_trunk_link_s {scalar_t__ state; scalar_t__ trunk_wwn; scalar_t__ fctl; scalar_t__ speed; int /*<<< orphan*/  deskew; } ;
struct bfa_trunk_link_attr_s {scalar_t__ link_state; scalar_t__ trunk_wwn; scalar_t__ fctl; scalar_t__ speed; scalar_t__ deskew; } ;
struct TYPE_5__ {scalar_t__ state; scalar_t__ speed; struct bfa_trunk_link_attr_s* link_attr; } ;
struct bfa_fcport_trunk_s {TYPE_2__ attr; } ;
struct TYPE_4__ {scalar_t__ trunked; } ;
struct bfa_fcport_s {scalar_t__ speed; TYPE_3__* bfa; int /*<<< orphan*/  topology; TYPE_1__ cfg; struct bfa_fcport_trunk_s trunk; } ;
typedef  enum bfa_trunk_state { ____Placeholder_bfa_trunk_state } bfa_trunk_state ;
struct TYPE_6__ {int /*<<< orphan*/  plog; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_PL_EID_TRUNK_SCN ; 
 int /*<<< orphan*/  BFA_PL_MID_HAL ; 
 int /*<<< orphan*/  BFA_PORT_LINKDOWN ; 
 int /*<<< orphan*/  BFA_PORT_LINKUP ; 
 int /*<<< orphan*/  BFA_PORT_TOPOLOGY_P2P ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 scalar_t__ BFA_TRUNK_DISABLED ; 
 scalar_t__ BFA_TRUNK_LINK_STATE_UP ; 
 int BFA_TRUNK_MAX_PORTS ; 
 scalar_t__ BFA_TRUNK_OFFLINE ; 
 scalar_t__ BFA_TRUNK_ONLINE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_scn (struct bfa_fcport_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_plog_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void
bfa_trunk_scn(struct bfa_fcport_s *fcport, struct bfi_fcport_trunk_scn_s *scn)
{
	struct bfa_fcport_trunk_s *trunk = &fcport->trunk;
	struct bfi_fcport_trunk_link_s *tlink;
	struct bfa_trunk_link_attr_s *lattr;
	enum bfa_trunk_state state_prev;
	int i;
	int link_bm = 0;

	bfa_trc(fcport->bfa, fcport->cfg.trunked);
	WARN_ON(scn->trunk_state != BFA_TRUNK_ONLINE &&
		   scn->trunk_state != BFA_TRUNK_OFFLINE);

	bfa_trc(fcport->bfa, trunk->attr.state);
	bfa_trc(fcport->bfa, scn->trunk_state);
	bfa_trc(fcport->bfa, scn->trunk_speed);

	/*
	 * Save off new state for trunk attribute query
	 */
	state_prev = trunk->attr.state;
	if (fcport->cfg.trunked && (trunk->attr.state != BFA_TRUNK_DISABLED))
		trunk->attr.state = scn->trunk_state;
	trunk->attr.speed = scn->trunk_speed;
	for (i = 0; i < BFA_TRUNK_MAX_PORTS; i++) {
		lattr = &trunk->attr.link_attr[i];
		tlink = &scn->tlink[i];

		lattr->link_state = tlink->state;
		lattr->trunk_wwn  = tlink->trunk_wwn;
		lattr->fctl	  = tlink->fctl;
		lattr->speed	  = tlink->speed;
		lattr->deskew	  = be32_to_cpu(tlink->deskew);

		if (tlink->state == BFA_TRUNK_LINK_STATE_UP) {
			fcport->speed	 = tlink->speed;
			fcport->topology = BFA_PORT_TOPOLOGY_P2P;
			link_bm |= 1 << i;
		}

		bfa_trc(fcport->bfa, lattr->link_state);
		bfa_trc(fcport->bfa, lattr->trunk_wwn);
		bfa_trc(fcport->bfa, lattr->fctl);
		bfa_trc(fcport->bfa, lattr->speed);
		bfa_trc(fcport->bfa, lattr->deskew);
	}

	switch (link_bm) {
	case 3:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk up(0,1)");
		break;
	case 2:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk up(-,1)");
		break;
	case 1:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk up(0,-)");
		break;
	default:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk down");
	}

	/*
	 * Notify upper layers if trunk state changed.
	 */
	if ((state_prev != trunk->attr.state) ||
		(scn->trunk_state == BFA_TRUNK_OFFLINE)) {
		bfa_fcport_scn(fcport, (scn->trunk_state == BFA_TRUNK_ONLINE) ?
			BFA_PORT_LINKUP : BFA_PORT_LINKDOWN, BFA_TRUE);
	}
}