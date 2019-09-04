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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct telemetry_evtconfig {int /*<<< orphan*/  period; void* num_evts; int /*<<< orphan*/ * evtmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  curr_period; } ;
struct TYPE_5__ {int /*<<< orphan*/  curr_period; } ;
struct TYPE_6__ {TYPE_1__ ioss_config; TYPE_2__ pss_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  TELEM_ADD ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int telemetry_setup_evtconfig (struct telemetry_evtconfig,struct telemetry_evtconfig,int /*<<< orphan*/ ) ; 
 TYPE_3__* telm_conf ; 

__attribute__((used)) static int telemetry_plt_add_events(u8 num_pss_evts, u8 num_ioss_evts,
				    u32 *pss_evtmap, u32 *ioss_evtmap)
{
	struct telemetry_evtconfig pss_evtconfig, ioss_evtconfig;
	int ret;

	pss_evtconfig.evtmap = pss_evtmap;
	pss_evtconfig.num_evts = num_pss_evts;
	pss_evtconfig.period = telm_conf->pss_config.curr_period;

	ioss_evtconfig.evtmap = ioss_evtmap;
	ioss_evtconfig.num_evts = num_ioss_evts;
	ioss_evtconfig.period = telm_conf->ioss_config.curr_period;

	ret = telemetry_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TELEM_ADD);
	if (ret)
		pr_err("TELEMETRY ADD Failed\n");

	return ret;
}