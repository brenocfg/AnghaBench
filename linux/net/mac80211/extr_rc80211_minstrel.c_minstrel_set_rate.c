#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct minstrel_sta_info {struct minstrel_rate* r; } ;
struct TYPE_3__ {int /*<<< orphan*/  retry_count_rtscts; } ;
struct minstrel_rate {TYPE_1__ stats; int /*<<< orphan*/  retry_count_cts; int /*<<< orphan*/  adjusted_retry_count; int /*<<< orphan*/  rix; } ;
struct ieee80211_sta_rates {TYPE_2__* rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  count_rts; int /*<<< orphan*/  count_cts; int /*<<< orphan*/  count; int /*<<< orphan*/  idx; } ;

/* Variables and functions */

__attribute__((used)) static void
minstrel_set_rate(struct minstrel_sta_info *mi, struct ieee80211_sta_rates *ratetbl,
		  int offset, int idx)
{
	struct minstrel_rate *r = &mi->r[idx];

	ratetbl->rate[offset].idx = r->rix;
	ratetbl->rate[offset].count = r->adjusted_retry_count;
	ratetbl->rate[offset].count_cts = r->retry_count_cts;
	ratetbl->rate[offset].count_rts = r->stats.retry_count_rtscts;
}