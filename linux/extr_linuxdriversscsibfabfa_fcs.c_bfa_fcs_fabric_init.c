#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bfa_lport_cfg_s {int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; int /*<<< orphan*/  roles; } ;
struct TYPE_6__ {struct bfa_lport_cfg_s port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_5__* fcs; TYPE_1__ bport; } ;
struct TYPE_10__ {TYPE_4__* bfa; } ;
struct TYPE_8__ {TYPE_2__* attr; } ;
struct TYPE_9__ {TYPE_3__ ioc; } ;
struct TYPE_7__ {int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LPORT_ROLE_FCP_IM ; 

__attribute__((used)) static void
bfa_fcs_fabric_init(struct bfa_fcs_fabric_s *fabric)
{
	struct bfa_lport_cfg_s *port_cfg = &fabric->bport.port_cfg;

	port_cfg->roles = BFA_LPORT_ROLE_FCP_IM;
	port_cfg->nwwn = fabric->fcs->bfa->ioc.attr->nwwn;
	port_cfg->pwwn = fabric->fcs->bfa->ioc.attr->pwwn;
}