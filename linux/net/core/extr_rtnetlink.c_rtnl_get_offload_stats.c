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
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int (* ndo_get_offload_stats ) (int,struct net_device*,void*) ;int /*<<< orphan*/  (* ndo_has_offload_stats ) (struct net_device*,int) ;} ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENODATA ; 
 int IFLA_OFFLOAD_XSTATS_FIRST ; 
 int IFLA_OFFLOAD_XSTATS_MAX ; 
 int /*<<< orphan*/  IFLA_OFFLOAD_XSTATS_UNSPEC ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 void* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve_64bit (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int rtnl_get_offload_stats_attr_size (int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int) ; 
 int stub2 (int,struct net_device*,void*) ; 

__attribute__((used)) static int rtnl_get_offload_stats(struct sk_buff *skb, struct net_device *dev,
				  int *prividx)
{
	struct nlattr *attr = NULL;
	int attr_id, size;
	void *attr_data;
	int err;

	if (!(dev->netdev_ops && dev->netdev_ops->ndo_has_offload_stats &&
	      dev->netdev_ops->ndo_get_offload_stats))
		return -ENODATA;

	for (attr_id = IFLA_OFFLOAD_XSTATS_FIRST;
	     attr_id <= IFLA_OFFLOAD_XSTATS_MAX; attr_id++) {
		if (attr_id < *prividx)
			continue;

		size = rtnl_get_offload_stats_attr_size(attr_id);
		if (!size)
			continue;

		if (!dev->netdev_ops->ndo_has_offload_stats(dev, attr_id))
			continue;

		attr = nla_reserve_64bit(skb, attr_id, size,
					 IFLA_OFFLOAD_XSTATS_UNSPEC);
		if (!attr)
			goto nla_put_failure;

		attr_data = nla_data(attr);
		memset(attr_data, 0, size);
		err = dev->netdev_ops->ndo_get_offload_stats(attr_id, dev,
							     attr_data);
		if (err)
			goto get_offload_stats_failure;
	}

	if (!attr)
		return -ENODATA;

	*prividx = 0;
	return 0;

nla_put_failure:
	err = -EMSGSIZE;
get_offload_stats_failure:
	*prividx = attr_id;
	return err;
}