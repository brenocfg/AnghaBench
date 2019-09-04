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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_p2p_noa_desc {int count; int /*<<< orphan*/  interval; int /*<<< orphan*/  duration; int /*<<< orphan*/  start_time; } ;
struct ieee80211_p2p_noa_attr {struct ieee80211_p2p_noa_desc* desc; } ;
struct ieee80211_noa_data {int* count; TYPE_1__* desc; } ;
struct TYPE_2__ {void* duration; void* interval; void* start; } ;

/* Variables and functions */
 int IEEE80211_P2P_NOA_DESC_MAX ; 
 int /*<<< orphan*/  ieee80211_extend_noa_desc (struct ieee80211_noa_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_update_p2p_noa (struct ieee80211_noa_data*,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_noa_data*,int /*<<< orphan*/ ,int) ; 

int ieee80211_parse_p2p_noa(const struct ieee80211_p2p_noa_attr *attr,
			    struct ieee80211_noa_data *data, u32 tsf)
{
	int ret = 0;
	int i;

	memset(data, 0, sizeof(*data));

	for (i = 0; i < IEEE80211_P2P_NOA_DESC_MAX; i++) {
		const struct ieee80211_p2p_noa_desc *desc = &attr->desc[i];

		if (!desc->count || !desc->duration)
			continue;

		data->count[i] = desc->count;
		data->desc[i].start = le32_to_cpu(desc->start_time);
		data->desc[i].duration = le32_to_cpu(desc->duration);
		data->desc[i].interval = le32_to_cpu(desc->interval);

		if (data->count[i] > 1 &&
		    data->desc[i].interval < data->desc[i].duration)
			continue;

		ieee80211_extend_noa_desc(data, tsf, i);
		ret++;
	}

	if (ret)
		ieee80211_update_p2p_noa(data, tsf);

	return ret;
}