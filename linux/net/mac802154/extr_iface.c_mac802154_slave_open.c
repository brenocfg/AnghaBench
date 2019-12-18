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
struct net_device {int dummy; } ;
struct ieee802154_sub_if_data {int /*<<< orphan*/  state; struct ieee802154_local* local; } ;
struct ieee802154_local {int /*<<< orphan*/  open_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  SDATA_STATE_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drv_start (struct ieee802154_local*) ; 
 int ieee802154_setup_hw (struct ieee802154_sub_if_data*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mac802154_slave_open(struct net_device *dev)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct ieee802154_local *local = sdata->local;
	int res;

	ASSERT_RTNL();

	set_bit(SDATA_STATE_RUNNING, &sdata->state);

	if (!local->open_count) {
		res = ieee802154_setup_hw(sdata);
		if (res)
			goto err;

		res = drv_start(local);
		if (res)
			goto err;
	}

	local->open_count++;
	netif_start_queue(dev);
	return 0;
err:
	/* might already be clear but that doesn't matter */
	clear_bit(SDATA_STATE_RUNNING, &sdata->state);

	return res;
}