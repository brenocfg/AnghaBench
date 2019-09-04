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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_time_event_data {int dummy; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iwl_mvm_remove_time_event (struct iwl_mvm*,struct iwl_mvm_time_event_data*,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_time_event_data* iwl_mvm_get_roc_te (struct iwl_mvm*) ; 

void iwl_mvm_cleanup_roc_te(struct iwl_mvm *mvm)
{
	struct iwl_mvm_time_event_data *te_data;
	u32 uid;

	te_data = iwl_mvm_get_roc_te(mvm);
	if (te_data)
		__iwl_mvm_remove_time_event(mvm, te_data, &uid);
}