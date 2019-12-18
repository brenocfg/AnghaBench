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
struct ieee80211_sub_if_data {int crypto_tx_tailroom_needed_cnt; int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  assert_key_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_vlan_tailroom_need_count (struct ieee80211_sub_if_data*,int) ; 

__attribute__((used)) static void decrease_tailroom_need_count(struct ieee80211_sub_if_data *sdata,
					 int delta)
{
	assert_key_lock(sdata->local);

	WARN_ON_ONCE(sdata->crypto_tx_tailroom_needed_cnt < delta);

	update_vlan_tailroom_need_count(sdata, -delta);
	sdata->crypto_tx_tailroom_needed_cnt -= delta;
}