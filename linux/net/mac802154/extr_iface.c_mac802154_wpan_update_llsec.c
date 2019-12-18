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
struct wpan_dev {int /*<<< orphan*/  extended_addr; int /*<<< orphan*/  pan_id; } ;
struct net_device {int dummy; } ;
struct ieee802154_sub_if_data {struct wpan_dev wpan_dev; } ;
struct ieee802154_mlme_ops {TYPE_1__* llsec; } ;
struct ieee802154_llsec_params {int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  pan_id; } ;
struct TYPE_2__ {int (* set_params ) (struct net_device*,struct ieee802154_llsec_params*,int) ;} ;

/* Variables and functions */
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE802154_LLSEC_PARAM_HWADDR ; 
 int IEEE802154_LLSEC_PARAM_PAN_ID ; 
 struct ieee802154_mlme_ops* ieee802154_mlme_ops (struct net_device*) ; 
 int stub1 (struct net_device*,struct ieee802154_llsec_params*,int) ; 

int mac802154_wpan_update_llsec(struct net_device *dev)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	struct wpan_dev *wpan_dev = &sdata->wpan_dev;
	int rc = 0;

	if (ops->llsec) {
		struct ieee802154_llsec_params params;
		int changed = 0;

		params.pan_id = wpan_dev->pan_id;
		changed |= IEEE802154_LLSEC_PARAM_PAN_ID;

		params.hwaddr = wpan_dev->extended_addr;
		changed |= IEEE802154_LLSEC_PARAM_HWADDR;

		rc = ops->llsec->set_params(dev, &params, changed);
	}

	return rc;
}