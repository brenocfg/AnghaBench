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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ifla_bridge_id {int dummy; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 

__attribute__((used)) static inline size_t br_port_info_size(void)
{
	return nla_total_size(1)	/* IFLA_BRPORT_STATE  */
		+ nla_total_size(2)	/* IFLA_BRPORT_PRIORITY */
		+ nla_total_size(4)	/* IFLA_BRPORT_COST */
		+ nla_total_size(1)	/* IFLA_BRPORT_MODE */
		+ nla_total_size(1)	/* IFLA_BRPORT_GUARD */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROTECT */
		+ nla_total_size(1)	/* IFLA_BRPORT_FAST_LEAVE */
		+ nla_total_size(1)	/* IFLA_BRPORT_MCAST_TO_UCAST */
		+ nla_total_size(1)	/* IFLA_BRPORT_LEARNING */
		+ nla_total_size(1)	/* IFLA_BRPORT_UNICAST_FLOOD */
		+ nla_total_size(1)	/* IFLA_BRPORT_MCAST_FLOOD */
		+ nla_total_size(1)	/* IFLA_BRPORT_BCAST_FLOOD */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROXYARP */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROXYARP_WIFI */
		+ nla_total_size(1)	/* IFLA_BRPORT_VLAN_TUNNEL */
		+ nla_total_size(1)	/* IFLA_BRPORT_NEIGH_SUPPRESS */
		+ nla_total_size(1)	/* IFLA_BRPORT_ISOLATED */
		+ nla_total_size(sizeof(struct ifla_bridge_id))	/* IFLA_BRPORT_ROOT_ID */
		+ nla_total_size(sizeof(struct ifla_bridge_id))	/* IFLA_BRPORT_BRIDGE_ID */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_DESIGNATED_PORT */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_DESIGNATED_COST */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_ID */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_NO */
		+ nla_total_size(sizeof(u8))	/* IFLA_BRPORT_TOPOLOGY_CHANGE_ACK */
		+ nla_total_size(sizeof(u8))	/* IFLA_BRPORT_CONFIG_PENDING */
		+ nla_total_size_64bit(sizeof(u64)) /* IFLA_BRPORT_MESSAGE_AGE_TIMER */
		+ nla_total_size_64bit(sizeof(u64)) /* IFLA_BRPORT_FORWARD_DELAY_TIMER */
		+ nla_total_size_64bit(sizeof(u64)) /* IFLA_BRPORT_HOLD_TIMER */
#ifdef CONFIG_BRIDGE_IGMP_SNOOPING
		+ nla_total_size(sizeof(u8))	/* IFLA_BRPORT_MULTICAST_ROUTER */
#endif
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_GROUP_FWD_MASK */
		+ 0;
}