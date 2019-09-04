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
struct rt2x00_dev {int /*<<< orphan*/  intf_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt2x00_dev*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mac_set_tim_iter ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rt2x00mac_set_tim(struct ieee80211_hw *hw, struct ieee80211_sta *sta,
		      bool set)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;

	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return 0;

	ieee80211_iterate_active_interfaces_atomic(
		rt2x00dev->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		rt2x00mac_set_tim_iter, rt2x00dev);

	/* queue work to upodate the beacon template */
	ieee80211_queue_work(rt2x00dev->hw, &rt2x00dev->intf_work);
	return 0;
}