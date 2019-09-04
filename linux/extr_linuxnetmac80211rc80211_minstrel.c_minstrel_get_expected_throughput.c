#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct minstrel_sta_info {int* max_tp_rate; TYPE_1__* r; } ;
struct minstrel_rate_stats {int /*<<< orphan*/  prob_ewma; } ;
struct TYPE_2__ {struct minstrel_rate_stats stats; } ;

/* Variables and functions */
 int minstrel_get_tp_avg (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 minstrel_get_expected_throughput(void *priv_sta)
{
	struct minstrel_sta_info *mi = priv_sta;
	struct minstrel_rate_stats *tmp_mrs;
	int idx = mi->max_tp_rate[0];
	int tmp_cur_tp;

	/* convert pkt per sec in kbps (1200 is the average pkt size used for
	 * computing cur_tp
	 */
	tmp_mrs = &mi->r[idx].stats;
	tmp_cur_tp = minstrel_get_tp_avg(&mi->r[idx], tmp_mrs->prob_ewma) * 10;
	tmp_cur_tp = tmp_cur_tp * 1200 * 8 / 1024;

	return tmp_cur_tp;
}