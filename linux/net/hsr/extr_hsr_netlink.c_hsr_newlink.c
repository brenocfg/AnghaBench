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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t IFLA_HSR_MULTICAST_SPEC ; 
 size_t IFLA_HSR_SLAVE1 ; 
 size_t IFLA_HSR_SLAVE2 ; 
 size_t IFLA_HSR_VERSION ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int hsr_dev_finalize (struct net_device*,struct net_device**,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 unsigned char nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int hsr_newlink(struct net *src_net, struct net_device *dev,
		       struct nlattr *tb[], struct nlattr *data[],
		       struct netlink_ext_ack *extack)
{
	struct net_device *link[2];
	unsigned char multicast_spec, hsr_version;

	if (!data) {
		netdev_info(dev, "HSR: No slave devices specified\n");
		return -EINVAL;
	}
	if (!data[IFLA_HSR_SLAVE1]) {
		netdev_info(dev, "HSR: Slave1 device not specified\n");
		return -EINVAL;
	}
	link[0] = __dev_get_by_index(src_net,
				     nla_get_u32(data[IFLA_HSR_SLAVE1]));
	if (!data[IFLA_HSR_SLAVE2]) {
		netdev_info(dev, "HSR: Slave2 device not specified\n");
		return -EINVAL;
	}
	link[1] = __dev_get_by_index(src_net,
				     nla_get_u32(data[IFLA_HSR_SLAVE2]));

	if (!link[0] || !link[1])
		return -ENODEV;
	if (link[0] == link[1])
		return -EINVAL;

	if (!data[IFLA_HSR_MULTICAST_SPEC])
		multicast_spec = 0;
	else
		multicast_spec = nla_get_u8(data[IFLA_HSR_MULTICAST_SPEC]);

	if (!data[IFLA_HSR_VERSION])
		hsr_version = 0;
	else
		hsr_version = nla_get_u8(data[IFLA_HSR_VERSION]);

	return hsr_dev_finalize(dev, link, multicast_spec, hsr_version);
}