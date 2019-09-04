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
 int /*<<< orphan*/  ieee802154_stop_device (struct ieee802154_local*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int mac802154_slave_close(struct net_device *dev)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct ieee802154_local *local = sdata->local;

	ASSERT_RTNL();

	netif_stop_queue(dev);
	local->open_count--;

	clear_bit(SDATA_STATE_RUNNING, &sdata->state);

	if (!local->open_count)
		ieee802154_stop_device(local);

	return 0;
}