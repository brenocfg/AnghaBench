#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct probe_resp {size_t* csa_counter_offsets; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_4__ {int /*<<< orphan*/  probe_resp; } ;
struct TYPE_5__ {TYPE_1__ ap; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; TYPE_2__ u; } ;
struct beacon_data {size_t tail_len; size_t head_len; size_t* csa_counter_offsets; int /*<<< orphan*/ * head; int /*<<< orphan*/ * tail; int /*<<< orphan*/  csa_current_counter; } ;

/* Variables and functions */
 int IEEE80211_MAX_CSA_COUNTERS_NUM ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_MESH_POINT 128 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct probe_resp* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void ieee80211_set_csa(struct ieee80211_sub_if_data *sdata,
			      struct beacon_data *beacon)
{
	struct probe_resp *resp;
	u8 *beacon_data;
	size_t beacon_data_len;
	int i;
	u8 count = beacon->csa_current_counter;

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
		beacon_data = beacon->tail;
		beacon_data_len = beacon->tail_len;
		break;
	case NL80211_IFTYPE_ADHOC:
		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
		break;
	case NL80211_IFTYPE_MESH_POINT:
		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
		break;
	default:
		return;
	}

	rcu_read_lock();
	for (i = 0; i < IEEE80211_MAX_CSA_COUNTERS_NUM; ++i) {
		resp = rcu_dereference(sdata->u.ap.probe_resp);

		if (beacon->csa_counter_offsets[i]) {
			if (WARN_ON_ONCE(beacon->csa_counter_offsets[i] >=
					 beacon_data_len)) {
				rcu_read_unlock();
				return;
			}

			beacon_data[beacon->csa_counter_offsets[i]] = count;
		}

		if (sdata->vif.type == NL80211_IFTYPE_AP && resp)
			resp->data[resp->csa_counter_offsets[i]] = count;
	}
	rcu_read_unlock();
}