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
struct ieee80211_sub_if_data {int /*<<< orphan*/  crypto_tx_tailroom_needed_cnt; int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_key_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  update_vlan_tailroom_need_count (struct ieee80211_sub_if_data*,int) ; 

__attribute__((used)) static void increment_tailroom_need_count(struct ieee80211_sub_if_data *sdata)
{
	/*
	 * When this count is zero, SKB resizing for allocating tailroom
	 * for IV or MMIC is skipped. But, this check has created two race
	 * cases in xmit path while transiting from zero count to one:
	 *
	 * 1. SKB resize was skipped because no key was added but just before
	 * the xmit key is added and SW encryption kicks off.
	 *
	 * 2. SKB resize was skipped because all the keys were hw planted but
	 * just before xmit one of the key is deleted and SW encryption kicks
	 * off.
	 *
	 * In both the above case SW encryption will find not enough space for
	 * tailroom and exits with WARN_ON. (See WARN_ONs at wpa.c)
	 *
	 * Solution has been explained at
	 * http://mid.gmane.org/1308590980.4322.19.camel@jlt3.sipsolutions.net
	 */

	assert_key_lock(sdata->local);

	update_vlan_tailroom_need_count(sdata, 1);

	if (!sdata->crypto_tx_tailroom_needed_cnt++) {
		/*
		 * Flush all XMIT packets currently using HW encryption or no
		 * encryption at all if the count transition is from 0 -> 1.
		 */
		synchronize_net();
	}
}