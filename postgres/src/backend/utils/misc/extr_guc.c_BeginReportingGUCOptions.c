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
struct config_generic {int flags; } ;

/* Variables and functions */
 scalar_t__ DestRemote ; 
 int /*<<< orphan*/  FrontendProtocol ; 
 int GUC_REPORT ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportGUCOption (struct config_generic*) ; 
 struct config_generic** guc_variables ; 
 int num_guc_variables ; 
 int reporting_enabled ; 
 scalar_t__ whereToSendOutput ; 

void
BeginReportingGUCOptions(void)
{
	int			i;

	/*
	 * Don't do anything unless talking to an interactive frontend of protocol
	 * 3.0 or later.
	 */
	if (whereToSendOutput != DestRemote ||
		PG_PROTOCOL_MAJOR(FrontendProtocol) < 3)
		return;

	reporting_enabled = true;

	/* Transmit initial values of interesting variables */
	for (i = 0; i < num_guc_variables; i++)
	{
		struct config_generic *conf = guc_variables[i];

		if (conf->flags & GUC_REPORT)
			ReportGUCOption(conf);
	}
}