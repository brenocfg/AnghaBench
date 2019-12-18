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
struct wpan_dev {int /*<<< orphan*/  frame_retries; int /*<<< orphan*/  csma_retries; int /*<<< orphan*/  max_be; int /*<<< orphan*/  min_be; int /*<<< orphan*/  lbt; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  extended_addr; int /*<<< orphan*/  pan_id; int /*<<< orphan*/  promiscuous_mode; } ;
struct ieee802154_sub_if_data {struct wpan_dev wpan_dev; struct ieee802154_local* local; } ;
struct TYPE_2__ {int flags; } ;
struct ieee802154_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int IEEE802154_HW_AFILT ; 
 int IEEE802154_HW_CSMA_PARAMS ; 
 int IEEE802154_HW_FRAME_RETRIES ; 
 int IEEE802154_HW_LBT ; 
 int IEEE802154_HW_PROMISCUOUS ; 
 int drv_set_csma_params (struct ieee802154_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drv_set_extended_addr (struct ieee802154_local*,int /*<<< orphan*/ ) ; 
 int drv_set_lbt_mode (struct ieee802154_local*,int /*<<< orphan*/ ) ; 
 int drv_set_max_frame_retries (struct ieee802154_local*,int /*<<< orphan*/ ) ; 
 int drv_set_pan_id (struct ieee802154_local*,int /*<<< orphan*/ ) ; 
 int drv_set_promiscuous_mode (struct ieee802154_local*,int /*<<< orphan*/ ) ; 
 int drv_set_short_addr (struct ieee802154_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee802154_setup_hw(struct ieee802154_sub_if_data *sdata)
{
	struct ieee802154_local *local = sdata->local;
	struct wpan_dev *wpan_dev = &sdata->wpan_dev;
	int ret;

	if (local->hw.flags & IEEE802154_HW_PROMISCUOUS) {
		ret = drv_set_promiscuous_mode(local,
					       wpan_dev->promiscuous_mode);
		if (ret < 0)
			return ret;
	}

	if (local->hw.flags & IEEE802154_HW_AFILT) {
		ret = drv_set_pan_id(local, wpan_dev->pan_id);
		if (ret < 0)
			return ret;

		ret = drv_set_extended_addr(local, wpan_dev->extended_addr);
		if (ret < 0)
			return ret;

		ret = drv_set_short_addr(local, wpan_dev->short_addr);
		if (ret < 0)
			return ret;
	}

	if (local->hw.flags & IEEE802154_HW_LBT) {
		ret = drv_set_lbt_mode(local, wpan_dev->lbt);
		if (ret < 0)
			return ret;
	}

	if (local->hw.flags & IEEE802154_HW_CSMA_PARAMS) {
		ret = drv_set_csma_params(local, wpan_dev->min_be,
					  wpan_dev->max_be,
					  wpan_dev->csma_retries);
		if (ret < 0)
			return ret;
	}

	if (local->hw.flags & IEEE802154_HW_FRAME_RETRIES) {
		ret = drv_set_max_frame_retries(local, wpan_dev->frame_retries);
		if (ret < 0)
			return ret;
	}

	return 0;
}