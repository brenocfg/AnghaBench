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
struct rs_rate {int index; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_3__ {scalar_t__ last_rssi; } ;
struct iwl_lq_sta {int optimal_rate_mask; int optimal_nentries; TYPE_2__* optimal_rates; TYPE_1__ pers; struct rs_rate optimal_rate; } ;
struct TYPE_4__ {int rate_idx; scalar_t__ rssi; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int find_first_bit (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rs_rate *rs_get_optimal_rate(struct iwl_mvm *mvm,
					   struct iwl_lq_sta *lq_sta)
{
	struct rs_rate *rate = &lq_sta->optimal_rate;
	int i;

	rate->index = find_first_bit(&lq_sta->optimal_rate_mask,
				     BITS_PER_LONG);

	for (i = 0; i < lq_sta->optimal_nentries; i++) {
		int rate_idx = lq_sta->optimal_rates[i].rate_idx;

		if ((lq_sta->pers.last_rssi >= lq_sta->optimal_rates[i].rssi) &&
		    (BIT(rate_idx) & lq_sta->optimal_rate_mask)) {
			rate->index = rate_idx;
			break;
		}
	}

	return rate;
}