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
struct iwl_tof_mcsi_notif {int /*<<< orphan*/  token; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_tof_mcsi_notif(struct iwl_mvm *mvm, void *data)
{
	struct iwl_tof_mcsi_notif *resp = (struct iwl_tof_mcsi_notif *)data;

	IWL_DEBUG_INFO(mvm, "MCSI notification, token %d\n", resp->token);
	return 0;
}