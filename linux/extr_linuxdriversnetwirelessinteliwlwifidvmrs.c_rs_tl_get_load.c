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
typedef  int u32 ;
struct iwl_traffic_load {int /*<<< orphan*/  time_stamp; int /*<<< orphan*/  queue_count; } ;
struct iwl_lq_sta {struct iwl_traffic_load* load; } ;
typedef  int s32 ;

/* Variables and functions */
 size_t IWL_MAX_TID_COUNT ; 
 int TID_QUEUE_CELL_SPACING ; 
 int TID_QUEUE_MAX_SIZE ; 
 int TID_ROUND_VALUE ; 
 int TIME_WRAP_AROUND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_tl_rm_old_stats (struct iwl_traffic_load*,int) ; 

__attribute__((used)) static void rs_tl_get_load(struct iwl_lq_sta *lq_data, u8 tid)
{
	u32 curr_time = jiffies_to_msecs(jiffies);
	u32 time_diff;
	s32 index;
	struct iwl_traffic_load *tl = NULL;

	if (tid >= IWL_MAX_TID_COUNT)
		return;

	tl = &(lq_data->load[tid]);

	curr_time -= curr_time % TID_ROUND_VALUE;

	if (!(tl->queue_count))
		return;

	time_diff = TIME_WRAP_AROUND(tl->time_stamp, curr_time);
	index = time_diff / TID_QUEUE_CELL_SPACING;

	/* The history is too long: remove data that is older than */
	/* TID_MAX_TIME_DIFF */
	if (index >= TID_QUEUE_MAX_SIZE)
		rs_tl_rm_old_stats(tl, curr_time);
}