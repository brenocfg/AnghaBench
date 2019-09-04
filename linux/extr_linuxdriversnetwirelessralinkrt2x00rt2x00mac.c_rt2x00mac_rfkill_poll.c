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
struct rt2x00_dev {TYPE_2__* ops; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rt2x00_dev* priv; } ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rfkill_poll ) (struct rt2x00_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

void rt2x00mac_rfkill_poll(struct ieee80211_hw *hw)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	bool active = !!rt2x00dev->ops->lib->rfkill_poll(rt2x00dev);

	wiphy_rfkill_set_hw_state(hw->wiphy, !active);
}