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
struct TYPE_3__ {int /*<<< orphan*/  min_cfg; int /*<<< orphan*/  num_rspq_elems; int /*<<< orphan*/  num_reqq_elems; int /*<<< orphan*/  num_sgpgs; } ;
struct TYPE_4__ {scalar_t__ num_fwtio_reqs; int /*<<< orphan*/  num_rports; int /*<<< orphan*/  num_uf_bufs; int /*<<< orphan*/  num_fcxp_reqs; int /*<<< orphan*/  num_tskim_reqs; int /*<<< orphan*/  num_ioim_reqs; } ;
struct bfa_iocfc_cfg_s {TYPE_1__ drvcfg; TYPE_2__ fwcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCXP_MIN ; 
 int /*<<< orphan*/  BFA_IOIM_MIN ; 
 int /*<<< orphan*/  BFA_REQQ_NELEMS_MIN ; 
 int /*<<< orphan*/  BFA_RPORT_MIN ; 
 int /*<<< orphan*/  BFA_RSPQ_NELEMS_MIN ; 
 int /*<<< orphan*/  BFA_SGPG_MIN ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFA_TSKIM_MIN ; 
 int /*<<< orphan*/  BFA_UF_MIN ; 
 int /*<<< orphan*/  bfa_cfg_get_default (struct bfa_iocfc_cfg_s*) ; 

void
bfa_cfg_get_min(struct bfa_iocfc_cfg_s *cfg)
{
	bfa_cfg_get_default(cfg);
	cfg->fwcfg.num_ioim_reqs   = BFA_IOIM_MIN;
	cfg->fwcfg.num_tskim_reqs  = BFA_TSKIM_MIN;
	cfg->fwcfg.num_fcxp_reqs   = BFA_FCXP_MIN;
	cfg->fwcfg.num_uf_bufs     = BFA_UF_MIN;
	cfg->fwcfg.num_rports      = BFA_RPORT_MIN;
	cfg->fwcfg.num_fwtio_reqs = 0;

	cfg->drvcfg.num_sgpgs      = BFA_SGPG_MIN;
	cfg->drvcfg.num_reqq_elems = BFA_REQQ_NELEMS_MIN;
	cfg->drvcfg.num_rspq_elems = BFA_RSPQ_NELEMS_MIN;
	cfg->drvcfg.min_cfg	   = BFA_TRUE;
}