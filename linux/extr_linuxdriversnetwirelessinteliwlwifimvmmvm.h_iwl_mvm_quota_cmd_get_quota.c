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
struct iwl_time_quota_data_v1 {int dummy; } ;
struct iwl_time_quota_data {int dummy; } ;
struct iwl_time_quota_cmd {struct iwl_time_quota_data* quotas; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ iwl_mvm_has_quota_low_latency (struct iwl_mvm*) ; 

__attribute__((used)) static inline struct iwl_time_quota_data
*iwl_mvm_quota_cmd_get_quota(struct iwl_mvm *mvm,
			     struct iwl_time_quota_cmd *cmd,
			     int i)
{
	struct iwl_time_quota_data_v1 *quotas;

	if (iwl_mvm_has_quota_low_latency(mvm))
		return &cmd->quotas[i];

	quotas = (struct iwl_time_quota_data_v1 *)cmd->quotas;
	return (struct iwl_time_quota_data *)&quotas[i];
}