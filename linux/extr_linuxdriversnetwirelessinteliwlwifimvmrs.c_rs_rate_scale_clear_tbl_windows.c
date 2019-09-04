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
struct iwl_scale_tbl_info {int /*<<< orphan*/ * tpc_win; int /*<<< orphan*/ * win; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*) ; 
 int IWL_RATE_COUNT ; 
 int /*<<< orphan*/  rs_rate_scale_clear_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_rate_scale_clear_tbl_windows(struct iwl_mvm *mvm,
					    struct iwl_scale_tbl_info *tbl)
{
	int i;

	IWL_DEBUG_RATE(mvm, "Clearing up window stats\n");
	for (i = 0; i < IWL_RATE_COUNT; i++)
		rs_rate_scale_clear_window(&tbl->win[i]);

	for (i = 0; i < ARRAY_SIZE(tbl->tpc_win); i++)
		rs_rate_scale_clear_window(&tbl->tpc_win[i]);
}