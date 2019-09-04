#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct telemetry_evtconfig {void* period; void* num_evts; int /*<<< orphan*/ * evtmap; } ;

/* Variables and functions */
 void* TELEM_MAX_OS_ALLOCATED_EVENTS ; 
 int /*<<< orphan*/  TELEM_RESET ; 
 void* TELEM_SAMPLING_DEFAULT_PERIOD ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int telemetry_setup_evtconfig (struct telemetry_evtconfig,struct telemetry_evtconfig,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int telemetry_plt_reset_events(void)
{
	struct telemetry_evtconfig pss_evtconfig, ioss_evtconfig;
	int ret;

	pss_evtconfig.evtmap = NULL;
	pss_evtconfig.num_evts = TELEM_MAX_OS_ALLOCATED_EVENTS;
	pss_evtconfig.period = TELEM_SAMPLING_DEFAULT_PERIOD;

	ioss_evtconfig.evtmap = NULL;
	ioss_evtconfig.num_evts = TELEM_MAX_OS_ALLOCATED_EVENTS;
	ioss_evtconfig.period = TELEM_SAMPLING_DEFAULT_PERIOD;

	ret = telemetry_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TELEM_RESET);
	if (ret)
		pr_err("TELEMETRY Reset Failed\n");

	return ret;
}