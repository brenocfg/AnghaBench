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
typedef  int /*<<< orphan*/  u32 ;
struct zd_mac {int /*<<< orphan*/  chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_conf {TYPE_2__ chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int zd_chip_set_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 

__attribute__((used)) static int zd_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct zd_mac *mac = zd_hw_mac(hw);
	struct ieee80211_conf *conf = &hw->conf;

	spin_lock_irq(&mac->lock);
	mac->channel = conf->chandef.chan->hw_value;
	spin_unlock_irq(&mac->lock);

	return zd_chip_set_channel(&mac->chip, conf->chandef.chan->hw_value);
}