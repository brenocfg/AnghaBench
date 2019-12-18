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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct net_bridge_port {int flags; int state; int topology_change_ack; int config_pending; int multicast_router; TYPE_1__* dev; int /*<<< orphan*/  backup_port; int /*<<< orphan*/  hold_timer; int /*<<< orphan*/  forward_delay_timer; int /*<<< orphan*/  message_age_timer; int /*<<< orphan*/  group_fwd_mask; int /*<<< orphan*/  port_no; int /*<<< orphan*/  port_id; int /*<<< orphan*/  designated_cost; int /*<<< orphan*/  designated_port; int /*<<< orphan*/  designated_bridge; int /*<<< orphan*/  designated_root; int /*<<< orphan*/  path_cost; int /*<<< orphan*/  priority; } ;
struct ifla_bridge_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int BR_BCAST_FLOOD ; 
 int BR_BPDU_GUARD ; 
 int BR_FLOOD ; 
 int BR_HAIRPIN_MODE ; 
 int BR_ISOLATED ; 
 int BR_LEARNING ; 
 int BR_MCAST_FLOOD ; 
 int BR_MULTICAST_FAST_LEAVE ; 
 int BR_MULTICAST_TO_UNICAST ; 
 int BR_NEIGH_SUPPRESS ; 
 int BR_PROXYARP ; 
 int BR_PROXYARP_WIFI ; 
 int BR_ROOT_BLOCK ; 
 int BR_VLAN_TUNNEL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_BRPORT_BACKUP_PORT ; 
 int /*<<< orphan*/  IFLA_BRPORT_BCAST_FLOOD ; 
 int /*<<< orphan*/  IFLA_BRPORT_BRIDGE_ID ; 
 int /*<<< orphan*/  IFLA_BRPORT_CONFIG_PENDING ; 
 int /*<<< orphan*/  IFLA_BRPORT_COST ; 
 int /*<<< orphan*/  IFLA_BRPORT_DESIGNATED_COST ; 
 int /*<<< orphan*/  IFLA_BRPORT_DESIGNATED_PORT ; 
 int /*<<< orphan*/  IFLA_BRPORT_FAST_LEAVE ; 
 int /*<<< orphan*/  IFLA_BRPORT_FORWARD_DELAY_TIMER ; 
 int /*<<< orphan*/  IFLA_BRPORT_GROUP_FWD_MASK ; 
 int /*<<< orphan*/  IFLA_BRPORT_GUARD ; 
 int /*<<< orphan*/  IFLA_BRPORT_HOLD_TIMER ; 
 int /*<<< orphan*/  IFLA_BRPORT_ID ; 
 int /*<<< orphan*/  IFLA_BRPORT_ISOLATED ; 
 int /*<<< orphan*/  IFLA_BRPORT_LEARNING ; 
 int /*<<< orphan*/  IFLA_BRPORT_MCAST_FLOOD ; 
 int /*<<< orphan*/  IFLA_BRPORT_MCAST_TO_UCAST ; 
 int /*<<< orphan*/  IFLA_BRPORT_MESSAGE_AGE_TIMER ; 
 int /*<<< orphan*/  IFLA_BRPORT_MODE ; 
 int /*<<< orphan*/  IFLA_BRPORT_MULTICAST_ROUTER ; 
 int /*<<< orphan*/  IFLA_BRPORT_NEIGH_SUPPRESS ; 
 int /*<<< orphan*/  IFLA_BRPORT_NO ; 
 int /*<<< orphan*/  IFLA_BRPORT_PAD ; 
 int /*<<< orphan*/  IFLA_BRPORT_PRIORITY ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROTECT ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROXYARP ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROXYARP_WIFI ; 
 int /*<<< orphan*/  IFLA_BRPORT_ROOT_ID ; 
 int /*<<< orphan*/  IFLA_BRPORT_STATE ; 
 int /*<<< orphan*/  IFLA_BRPORT_TOPOLOGY_CHANGE_ACK ; 
 int /*<<< orphan*/  IFLA_BRPORT_UNICAST_FLOOD ; 
 int /*<<< orphan*/  IFLA_BRPORT_VLAN_TUNNEL ; 
 int /*<<< orphan*/  br_timer_value (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct net_bridge_port* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int br_port_fill_attrs(struct sk_buff *skb,
			      const struct net_bridge_port *p)
{
	u8 mode = !!(p->flags & BR_HAIRPIN_MODE);
	struct net_bridge_port *backup_p;
	u64 timerval;

	if (nla_put_u8(skb, IFLA_BRPORT_STATE, p->state) ||
	    nla_put_u16(skb, IFLA_BRPORT_PRIORITY, p->priority) ||
	    nla_put_u32(skb, IFLA_BRPORT_COST, p->path_cost) ||
	    nla_put_u8(skb, IFLA_BRPORT_MODE, mode) ||
	    nla_put_u8(skb, IFLA_BRPORT_GUARD, !!(p->flags & BR_BPDU_GUARD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_PROTECT,
		       !!(p->flags & BR_ROOT_BLOCK)) ||
	    nla_put_u8(skb, IFLA_BRPORT_FAST_LEAVE,
		       !!(p->flags & BR_MULTICAST_FAST_LEAVE)) ||
	    nla_put_u8(skb, IFLA_BRPORT_MCAST_TO_UCAST,
		       !!(p->flags & BR_MULTICAST_TO_UNICAST)) ||
	    nla_put_u8(skb, IFLA_BRPORT_LEARNING, !!(p->flags & BR_LEARNING)) ||
	    nla_put_u8(skb, IFLA_BRPORT_UNICAST_FLOOD,
		       !!(p->flags & BR_FLOOD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_MCAST_FLOOD,
		       !!(p->flags & BR_MCAST_FLOOD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_BCAST_FLOOD,
		       !!(p->flags & BR_BCAST_FLOOD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_PROXYARP, !!(p->flags & BR_PROXYARP)) ||
	    nla_put_u8(skb, IFLA_BRPORT_PROXYARP_WIFI,
		       !!(p->flags & BR_PROXYARP_WIFI)) ||
	    nla_put(skb, IFLA_BRPORT_ROOT_ID, sizeof(struct ifla_bridge_id),
		    &p->designated_root) ||
	    nla_put(skb, IFLA_BRPORT_BRIDGE_ID, sizeof(struct ifla_bridge_id),
		    &p->designated_bridge) ||
	    nla_put_u16(skb, IFLA_BRPORT_DESIGNATED_PORT, p->designated_port) ||
	    nla_put_u16(skb, IFLA_BRPORT_DESIGNATED_COST, p->designated_cost) ||
	    nla_put_u16(skb, IFLA_BRPORT_ID, p->port_id) ||
	    nla_put_u16(skb, IFLA_BRPORT_NO, p->port_no) ||
	    nla_put_u8(skb, IFLA_BRPORT_TOPOLOGY_CHANGE_ACK,
		       p->topology_change_ack) ||
	    nla_put_u8(skb, IFLA_BRPORT_CONFIG_PENDING, p->config_pending) ||
	    nla_put_u8(skb, IFLA_BRPORT_VLAN_TUNNEL, !!(p->flags &
							BR_VLAN_TUNNEL)) ||
	    nla_put_u16(skb, IFLA_BRPORT_GROUP_FWD_MASK, p->group_fwd_mask) ||
	    nla_put_u8(skb, IFLA_BRPORT_NEIGH_SUPPRESS,
		       !!(p->flags & BR_NEIGH_SUPPRESS)) ||
	    nla_put_u8(skb, IFLA_BRPORT_ISOLATED, !!(p->flags & BR_ISOLATED)))
		return -EMSGSIZE;

	timerval = br_timer_value(&p->message_age_timer);
	if (nla_put_u64_64bit(skb, IFLA_BRPORT_MESSAGE_AGE_TIMER, timerval,
			      IFLA_BRPORT_PAD))
		return -EMSGSIZE;
	timerval = br_timer_value(&p->forward_delay_timer);
	if (nla_put_u64_64bit(skb, IFLA_BRPORT_FORWARD_DELAY_TIMER, timerval,
			      IFLA_BRPORT_PAD))
		return -EMSGSIZE;
	timerval = br_timer_value(&p->hold_timer);
	if (nla_put_u64_64bit(skb, IFLA_BRPORT_HOLD_TIMER, timerval,
			      IFLA_BRPORT_PAD))
		return -EMSGSIZE;

#ifdef CONFIG_BRIDGE_IGMP_SNOOPING
	if (nla_put_u8(skb, IFLA_BRPORT_MULTICAST_ROUTER,
		       p->multicast_router))
		return -EMSGSIZE;
#endif

	/* we might be called only with br->lock */
	rcu_read_lock();
	backup_p = rcu_dereference(p->backup_port);
	if (backup_p)
		nla_put_u32(skb, IFLA_BRPORT_BACKUP_PORT,
			    backup_p->dev->ifindex);
	rcu_read_unlock();

	return 0;
}