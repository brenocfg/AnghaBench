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
struct iwl_tof_neighbor_report {int /*<<< orphan*/  status; int /*<<< orphan*/  request_token; int /*<<< orphan*/  bssid; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_tof_nb_report_notif(struct iwl_mvm *mvm, void *data)
{
	struct iwl_tof_neighbor_report *report =
		(struct iwl_tof_neighbor_report *)data;

	IWL_DEBUG_INFO(mvm, "NB report, bssid %pM, token %d, status 0x%x\n",
		       report->bssid, report->request_token, report->status);
	return 0;
}