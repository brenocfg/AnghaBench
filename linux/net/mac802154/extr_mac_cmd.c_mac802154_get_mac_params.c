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
struct wpan_dev {int /*<<< orphan*/  lbt; int /*<<< orphan*/  frame_retries; int /*<<< orphan*/  csma_retries; int /*<<< orphan*/  max_be; int /*<<< orphan*/  min_be; TYPE_1__* wpan_phy; } ;
struct net_device {int dummy; } ;
struct ieee802154_sub_if_data {struct wpan_dev wpan_dev; } ;
struct ieee802154_mac_params {int /*<<< orphan*/  lbt; int /*<<< orphan*/  frame_retries; int /*<<< orphan*/  csma_retries; int /*<<< orphan*/  max_be; int /*<<< orphan*/  min_be; int /*<<< orphan*/  cca_ed_level; int /*<<< orphan*/  cca; int /*<<< orphan*/  transmit_power; } ;
struct TYPE_2__ {int /*<<< orphan*/  cca_ed_level; int /*<<< orphan*/  cca; int /*<<< orphan*/  transmit_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 

__attribute__((used)) static void mac802154_get_mac_params(struct net_device *dev,
				     struct ieee802154_mac_params *params)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct wpan_dev *wpan_dev = &sdata->wpan_dev;

	ASSERT_RTNL();

	/* PHY */
	params->transmit_power = wpan_dev->wpan_phy->transmit_power;
	params->cca = wpan_dev->wpan_phy->cca;
	params->cca_ed_level = wpan_dev->wpan_phy->cca_ed_level;

	/* MAC */
	params->min_be = wpan_dev->min_be;
	params->max_be = wpan_dev->max_be;
	params->csma_retries = wpan_dev->csma_retries;
	params->frame_retries = wpan_dev->frame_retries;
	params->lbt = wpan_dev->lbt;
}