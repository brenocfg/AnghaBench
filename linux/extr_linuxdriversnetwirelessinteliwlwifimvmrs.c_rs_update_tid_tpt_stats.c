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
typedef  size_t u8 ;
struct iwl_mvm_tid_data {scalar_t__ state; scalar_t__ tx_count; scalar_t__ tx_count_last; scalar_t__ tpt_meas_start; } ;
struct iwl_mvm_sta {struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 scalar_t__ IWL_AGG_OFF ; 
 size_t IWL_MAX_TID_COUNT ; 
 scalar_t__ IWL_MVM_RS_AGG_START_THRESHOLD ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static void rs_update_tid_tpt_stats(struct iwl_mvm *mvm,
				    struct iwl_mvm_sta *mvmsta,
				    u8 tid, int successes)
{
	struct iwl_mvm_tid_data *tid_data;

	if (tid >= IWL_MAX_TID_COUNT)
		return;

	tid_data = &mvmsta->tid_data[tid];

	/*
	 * Measure if there're enough successful transmits per second.
	 * These statistics are used only to decide if we can start a
	 * BA session, so it should be updated only when A-MPDU is
	 * off.
	 */
	if (tid_data->state != IWL_AGG_OFF)
		return;

	if (time_is_before_jiffies(tid_data->tpt_meas_start + HZ) ||
	    (tid_data->tx_count >= IWL_MVM_RS_AGG_START_THRESHOLD)) {
		tid_data->tx_count_last = tid_data->tx_count;
		tid_data->tx_count = 0;
		tid_data->tpt_meas_start = jiffies;
	} else {
		tid_data->tx_count += successes;
	}
}