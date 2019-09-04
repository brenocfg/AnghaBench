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
struct sk_buff {int dummy; } ;
typedef  struct net_device net_device ;
struct genl_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  llsec; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 TYPE_1__* ieee802154_mlme_ops (struct net_device*) ; 
 struct net_device* ieee802154_nl_get_dev (struct genl_info*) ; 

__attribute__((used)) static int
ieee802154_nl_llsec_change(struct sk_buff *skb, struct genl_info *info,
			   int (*fn)(struct net_device*, struct genl_info*))
{
	struct net_device *dev = NULL;
	int rc = -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	if (!dev)
		return -ENODEV;

	if (!ieee802154_mlme_ops(dev)->llsec)
		rc = -EOPNOTSUPP;
	else
		rc = fn(dev, info);

	dev_put(dev);
	return rc;
}