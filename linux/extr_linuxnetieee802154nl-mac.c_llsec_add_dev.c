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
struct net_device {int dummy; } ;
struct ieee802154_mlme_ops {TYPE_1__* llsec; } ;
struct ieee802154_llsec_device {int dummy; } ;
struct genl_info {int dummy; } ;
struct TYPE_2__ {int (* add_dev ) (struct net_device*,struct ieee802154_llsec_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct ieee802154_mlme_ops* ieee802154_mlme_ops (struct net_device*) ; 
 scalar_t__ llsec_parse_dev (struct genl_info*,struct ieee802154_llsec_device*) ; 
 int stub1 (struct net_device*,struct ieee802154_llsec_device*) ; 

__attribute__((used)) static int llsec_add_dev(struct net_device *dev, struct genl_info *info)
{
	struct ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	struct ieee802154_llsec_device desc;

	if (llsec_parse_dev(info, &desc))
		return -EINVAL;

	return ops->llsec->add_dev(dev, &desc);
}