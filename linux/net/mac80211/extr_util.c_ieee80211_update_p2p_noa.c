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
typedef  scalar_t__ u32 ;
struct ieee80211_noa_data {int absent; int has_next_tsf; scalar_t__ next_tsf; TYPE_1__* desc; int /*<<< orphan*/ * count; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_P2P_NOA_DESC_MAX ; 
 int /*<<< orphan*/  ieee80211_extend_noa_desc (struct ieee80211_noa_data*,scalar_t__,int) ; 
 scalar_t__ ieee80211_get_noa_absent_time (struct ieee80211_noa_data*,scalar_t__) ; 

void ieee80211_update_p2p_noa(struct ieee80211_noa_data *data, u32 tsf)
{
	u32 next_offset = BIT(31) - 1;
	int i;

	data->absent = 0;
	data->has_next_tsf = false;
	for (i = 0; i < IEEE80211_P2P_NOA_DESC_MAX; i++) {
		s32 start;

		if (!data->count[i])
			continue;

		ieee80211_extend_noa_desc(data, tsf, i);
		start = data->desc[i].start - tsf;
		if (start <= 0)
			data->absent |= BIT(i);

		if (next_offset > start)
			next_offset = start;

		data->has_next_tsf = true;
	}

	if (data->absent)
		next_offset = ieee80211_get_noa_absent_time(data, tsf);

	data->next_tsf = tsf + next_offset;
}