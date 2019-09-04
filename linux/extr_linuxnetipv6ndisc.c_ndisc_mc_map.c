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
struct net_device {int type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  broadcast; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  ARPHRD_ARCNET 133 
#define  ARPHRD_ETHER 132 
#define  ARPHRD_FDDI 131 
#define  ARPHRD_IEEE802 130 
#define  ARPHRD_INFINIBAND 129 
#define  ARPHRD_IPGRE 128 
 int EINVAL ; 
 int /*<<< orphan*/  ipv6_arcnet_mc_map (struct in6_addr const*,char*) ; 
 int /*<<< orphan*/  ipv6_eth_mc_map (struct in6_addr const*,char*) ; 
 int /*<<< orphan*/  ipv6_ib_mc_map (struct in6_addr const*,int /*<<< orphan*/ ,char*) ; 
 int ipv6_ipgre_mc_map (struct in6_addr const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ndisc_mc_map(const struct in6_addr *addr, char *buf, struct net_device *dev, int dir)
{
	switch (dev->type) {
	case ARPHRD_ETHER:
	case ARPHRD_IEEE802:	/* Not sure. Check it later. --ANK */
	case ARPHRD_FDDI:
		ipv6_eth_mc_map(addr, buf);
		return 0;
	case ARPHRD_ARCNET:
		ipv6_arcnet_mc_map(addr, buf);
		return 0;
	case ARPHRD_INFINIBAND:
		ipv6_ib_mc_map(addr, dev->broadcast, buf);
		return 0;
	case ARPHRD_IPGRE:
		return ipv6_ipgre_mc_map(addr, dev->broadcast, buf);
	default:
		if (dir) {
			memcpy(buf, dev->broadcast, dev->addr_len);
			return 0;
		}
	}
	return -EINVAL;
}