#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  function; } ;
struct ieee802154_local {int /*<<< orphan*/  workqueue; TYPE_3__* phy; TYPE_1__ hw; TYPE_8__ ifs_timer; } ;
struct ieee802154_hw {int flags; } ;
struct TYPE_10__ {int min_csma_backoffs; int max_csma_backoffs; int min_maxbe; int max_maxbe; int min_minbe; int max_minbe; int min_frame_retries; int max_frame_retries; int /*<<< orphan*/  iftypes; } ;
struct TYPE_11__ {TYPE_2__ supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int IEEE802154_HW_CSMA_PARAMS ; 
 int IEEE802154_HW_FRAME_RETRIES ; 
 int IEEE802154_HW_PROMISCUOUS ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  NET_NAME_ENUM ; 
 int /*<<< orphan*/  NL802154_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  NL802154_IFTYPE_NODE ; 
 int PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee802154_local* hw_to_local (struct ieee802154_hw*) ; 
 struct net_device* ieee802154_if_add (struct ieee802154_local*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_setup_wpan_phy_pib (TYPE_3__*) ; 
 int /*<<< orphan*/  ieee802154_xmit_ifs_timer ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  wpan_phy_name (TYPE_3__*) ; 
 int wpan_phy_register (TYPE_3__*) ; 
 int /*<<< orphan*/  wpan_phy_set_dev (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpan_phy_unregister (TYPE_3__*) ; 

int ieee802154_register_hw(struct ieee802154_hw *hw)
{
	struct ieee802154_local *local = hw_to_local(hw);
	struct net_device *dev;
	int rc = -ENOSYS;

	local->workqueue =
		create_singlethread_workqueue(wpan_phy_name(local->phy));
	if (!local->workqueue) {
		rc = -ENOMEM;
		goto out;
	}

	hrtimer_init(&local->ifs_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	local->ifs_timer.function = ieee802154_xmit_ifs_timer;

	wpan_phy_set_dev(local->phy, local->hw.parent);

	ieee802154_setup_wpan_phy_pib(local->phy);

	if (!(hw->flags & IEEE802154_HW_CSMA_PARAMS)) {
		local->phy->supported.min_csma_backoffs = 4;
		local->phy->supported.max_csma_backoffs = 4;
		local->phy->supported.min_maxbe = 5;
		local->phy->supported.max_maxbe = 5;
		local->phy->supported.min_minbe = 3;
		local->phy->supported.max_minbe = 3;
	}

	if (!(hw->flags & IEEE802154_HW_FRAME_RETRIES)) {
		local->phy->supported.min_frame_retries = 3;
		local->phy->supported.max_frame_retries = 3;
	}

	if (hw->flags & IEEE802154_HW_PROMISCUOUS)
		local->phy->supported.iftypes |= BIT(NL802154_IFTYPE_MONITOR);

	rc = wpan_phy_register(local->phy);
	if (rc < 0)
		goto out_wq;

	rtnl_lock();

	dev = ieee802154_if_add(local, "wpan%d", NET_NAME_ENUM,
				NL802154_IFTYPE_NODE,
				cpu_to_le64(0x0000000000000000ULL));
	if (IS_ERR(dev)) {
		rtnl_unlock();
		rc = PTR_ERR(dev);
		goto out_phy;
	}

	rtnl_unlock();

	return 0;

out_phy:
	wpan_phy_unregister(local->phy);
out_wq:
	destroy_workqueue(local->workqueue);
out:
	return rc;
}