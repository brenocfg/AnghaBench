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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int type; } ;

/* Variables and functions */
#define  ARPHRD_6LOWPAN 139 
#define  ARPHRD_ARCNET 138 
#define  ARPHRD_ETHER 137 
#define  ARPHRD_FDDI 136 
#define  ARPHRD_IEEE1394 135 
#define  ARPHRD_INFINIBAND 134 
#define  ARPHRD_IP6GRE 133 
#define  ARPHRD_IPGRE 132 
#define  ARPHRD_RAWIP 131 
#define  ARPHRD_SIT 130 
#define  ARPHRD_TUNNEL 129 
#define  ARPHRD_TUNNEL6 128 
 int addrconf_ifid_6lowpan (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_arcnet (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_eui48 (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_gre (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_ieee1394 (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_infiniband (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_ip6tnl (int /*<<< orphan*/ *,struct net_device*) ; 
 int addrconf_ifid_sit (int /*<<< orphan*/ *,struct net_device*) ; 

__attribute__((used)) static int ipv6_generate_eui64(u8 *eui, struct net_device *dev)
{
	switch (dev->type) {
	case ARPHRD_ETHER:
	case ARPHRD_FDDI:
		return addrconf_ifid_eui48(eui, dev);
	case ARPHRD_ARCNET:
		return addrconf_ifid_arcnet(eui, dev);
	case ARPHRD_INFINIBAND:
		return addrconf_ifid_infiniband(eui, dev);
	case ARPHRD_SIT:
		return addrconf_ifid_sit(eui, dev);
	case ARPHRD_IPGRE:
	case ARPHRD_TUNNEL:
		return addrconf_ifid_gre(eui, dev);
	case ARPHRD_6LOWPAN:
		return addrconf_ifid_6lowpan(eui, dev);
	case ARPHRD_IEEE1394:
		return addrconf_ifid_ieee1394(eui, dev);
	case ARPHRD_TUNNEL6:
	case ARPHRD_IP6GRE:
	case ARPHRD_RAWIP:
		return addrconf_ifid_ip6tnl(eui, dev);
	}
	return -1;
}