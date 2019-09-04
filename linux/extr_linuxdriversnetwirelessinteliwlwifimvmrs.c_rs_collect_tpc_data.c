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
struct iwl_scale_tbl_info {struct iwl_rate_scale_data* tpc_win; } ;
struct iwl_rate_scale_data {int dummy; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TPC_MAX_REDUCTION ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int _rs_collect_tx_data (struct iwl_mvm*,struct iwl_scale_tbl_info*,int,int,int,struct iwl_rate_scale_data*) ; 

__attribute__((used)) static int rs_collect_tpc_data(struct iwl_mvm *mvm,
			       struct iwl_lq_sta *lq_sta,
			       struct iwl_scale_tbl_info *tbl,
			       int scale_index, int attempts, int successes,
			       u8 reduced_txp)
{
	struct iwl_rate_scale_data *window = NULL;

	if (WARN_ON_ONCE(reduced_txp > TPC_MAX_REDUCTION))
		return -EINVAL;

	window = &tbl->tpc_win[reduced_txp];
	return  _rs_collect_tx_data(mvm, tbl, scale_index, attempts, successes,
				    window);
}