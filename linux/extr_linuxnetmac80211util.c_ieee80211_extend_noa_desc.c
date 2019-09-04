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
struct ieee80211_noa_data {int* count; TYPE_1__* desc; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int interval; scalar_t__ start; scalar_t__ duration; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int) ; 

__attribute__((used)) static bool
ieee80211_extend_noa_desc(struct ieee80211_noa_data *data, u32 tsf, int i)
{
	s32 end = data->desc[i].start + data->desc[i].duration - (tsf + 1);
	int skip;

	if (end > 0)
		return false;

	/* One shot NOA  */
	if (data->count[i] == 1)
		return false;

	if (data->desc[i].interval == 0)
		return false;

	/* End time is in the past, check for repetitions */
	skip = DIV_ROUND_UP(-end, data->desc[i].interval);
	if (data->count[i] < 255) {
		if (data->count[i] <= skip) {
			data->count[i] = 0;
			return false;
		}

		data->count[i] -= skip;
	}

	data->desc[i].start += skip * data->desc[i].interval;

	return true;
}