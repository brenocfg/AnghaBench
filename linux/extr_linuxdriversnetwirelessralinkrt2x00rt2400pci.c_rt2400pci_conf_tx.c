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
typedef  scalar_t__ u16 ;
struct rt2x00_dev {TYPE_1__* tx; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int dummy; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  rt2400pci_config_cw (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00mac_conf_tx (struct ieee80211_hw*,struct ieee80211_vif*,scalar_t__,struct ieee80211_tx_queue_params const*) ; 

__attribute__((used)) static int rt2400pci_conf_tx(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif, u16 queue,
			     const struct ieee80211_tx_queue_params *params)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * We don't support variating cw_min and cw_max variables
	 * per queue. So by default we only configure the TX queue,
	 * and ignore all other configurations.
	 */
	if (queue != 0)
		return -EINVAL;

	if (rt2x00mac_conf_tx(hw, vif, queue, params))
		return -EINVAL;

	/*
	 * Write configuration to register.
	 */
	rt2400pci_config_cw(rt2x00dev,
			    rt2x00dev->tx->cw_min, rt2x00dev->tx->cw_max);

	return 0;
}