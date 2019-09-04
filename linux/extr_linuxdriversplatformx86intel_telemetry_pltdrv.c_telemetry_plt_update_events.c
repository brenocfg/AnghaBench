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
struct telemetry_evtconfig {scalar_t__ num_evts; int /*<<< orphan*/  period; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TELEM_SAMPLE_PERIOD_INVALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TELEM_UPDATE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int telemetry_setup_evtconfig (struct telemetry_evtconfig,struct telemetry_evtconfig,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int telemetry_plt_update_events(struct telemetry_evtconfig pss_evtconfig,
				struct telemetry_evtconfig ioss_evtconfig)
{
	int ret;

	if ((pss_evtconfig.num_evts > 0) &&
	    (TELEM_SAMPLE_PERIOD_INVALID(pss_evtconfig.period))) {
		pr_err("PSS Sampling Period Out of Range\n");
		return -EINVAL;
	}

	if ((ioss_evtconfig.num_evts > 0) &&
	    (TELEM_SAMPLE_PERIOD_INVALID(ioss_evtconfig.period))) {
		pr_err("IOSS Sampling Period Out of Range\n");
		return -EINVAL;
	}

	ret = telemetry_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TELEM_UPDATE);
	if (ret)
		pr_err("TELEMETRY Config Failed\n");

	return ret;
}