#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_lport_cfg_s {int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; } ;
struct bfa_ioc_s {TYPE_1__* attr; } ;
struct TYPE_6__ {struct bfa_lport_cfg_s port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_4__* fcs; TYPE_2__ bport; } ;
struct bfa_fcs_s {struct bfa_fcs_fabric_s fabric; } ;
struct TYPE_8__ {TYPE_3__* bfa; } ;
struct TYPE_7__ {struct bfa_ioc_s ioc; } ;
struct TYPE_5__ {int /*<<< orphan*/  pwwn; int /*<<< orphan*/  nwwn; } ;

/* Variables and functions */

void
bfa_fcs_update_cfg(struct bfa_fcs_s *fcs)
{
	struct bfa_fcs_fabric_s *fabric = &fcs->fabric;
	struct bfa_lport_cfg_s *port_cfg = &fabric->bport.port_cfg;
	struct bfa_ioc_s *ioc = &fabric->fcs->bfa->ioc;

	port_cfg->nwwn = ioc->attr->nwwn;
	port_cfg->pwwn = ioc->attr->pwwn;
}