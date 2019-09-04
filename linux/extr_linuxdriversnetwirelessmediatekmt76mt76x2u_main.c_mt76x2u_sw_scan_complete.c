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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x2u_sw_scan_complete(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct mt76x2_dev *dev = hw->priv;

	clear_bit(MT76_SCANNING, &dev->mt76.state);
}