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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net_bridge_port {unsigned long flags; int group_fwd_mask; int /*<<< orphan*/  dev; int /*<<< orphan*/  br; } ;

/* Variables and functions */
 int BR_BCAST_FLOOD ; 
 int BR_BPDU_GUARD ; 
 int BR_FLOOD ; 
 int BR_GROUPFWD_MACPAUSE ; 
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
 int EINVAL ; 
 int ENOENT ; 
 size_t IFLA_BRPORT_BACKUP_PORT ; 
 int /*<<< orphan*/  IFLA_BRPORT_BCAST_FLOOD ; 
 size_t IFLA_BRPORT_COST ; 
 int /*<<< orphan*/  IFLA_BRPORT_FAST_LEAVE ; 
 size_t IFLA_BRPORT_FLUSH ; 
 size_t IFLA_BRPORT_GROUP_FWD_MASK ; 
 int /*<<< orphan*/  IFLA_BRPORT_GUARD ; 
 int /*<<< orphan*/  IFLA_BRPORT_ISOLATED ; 
 int /*<<< orphan*/  IFLA_BRPORT_LEARNING ; 
 int /*<<< orphan*/  IFLA_BRPORT_MCAST_FLOOD ; 
 int /*<<< orphan*/  IFLA_BRPORT_MCAST_TO_UCAST ; 
 int /*<<< orphan*/  IFLA_BRPORT_MODE ; 
 size_t IFLA_BRPORT_MULTICAST_ROUTER ; 
 int /*<<< orphan*/  IFLA_BRPORT_NEIGH_SUPPRESS ; 
 size_t IFLA_BRPORT_PRIORITY ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROTECT ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROXYARP ; 
 int /*<<< orphan*/  IFLA_BRPORT_PROXYARP_WIFI ; 
 size_t IFLA_BRPORT_STATE ; 
 int /*<<< orphan*/  IFLA_BRPORT_UNICAST_FLOOD ; 
 int /*<<< orphan*/  IFLA_BRPORT_VLAN_TUNNEL ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  br_fdb_delete_by_port (int /*<<< orphan*/ ,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_multicast_set_port_router (struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_port_flags_change (struct net_bridge_port*,unsigned long) ; 
 int br_set_port_flag (struct net_bridge_port*,struct nlattr**,int /*<<< orphan*/ ,int) ; 
 int br_set_port_state (struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int br_stp_set_path_cost (struct net_bridge_port*,scalar_t__) ; 
 int br_stp_set_port_priority (struct net_bridge_port*,int) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int nbp_backup_change (struct net_bridge_port*,struct net_device*) ; 
 int /*<<< orphan*/  nbp_vlan_tunnel_info_flush (struct net_bridge_port*) ; 
 int nla_get_u16 (struct nlattr*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int br_setport(struct net_bridge_port *p, struct nlattr *tb[])
{
	unsigned long old_flags = p->flags;
	bool br_vlan_tunnel_old = false;
	int err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_MODE, BR_HAIRPIN_MODE);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_GUARD, BR_BPDU_GUARD);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_FAST_LEAVE, BR_MULTICAST_FAST_LEAVE);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_PROTECT, BR_ROOT_BLOCK);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_LEARNING, BR_LEARNING);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_UNICAST_FLOOD, BR_FLOOD);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_MCAST_FLOOD, BR_MCAST_FLOOD);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_MCAST_TO_UCAST, BR_MULTICAST_TO_UNICAST);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_BCAST_FLOOD, BR_BCAST_FLOOD);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_PROXYARP, BR_PROXYARP);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_PROXYARP_WIFI, BR_PROXYARP_WIFI);
	if (err)
		return err;

	br_vlan_tunnel_old = (p->flags & BR_VLAN_TUNNEL) ? true : false;
	err = br_set_port_flag(p, tb, IFLA_BRPORT_VLAN_TUNNEL, BR_VLAN_TUNNEL);
	if (err)
		return err;

	if (br_vlan_tunnel_old && !(p->flags & BR_VLAN_TUNNEL))
		nbp_vlan_tunnel_info_flush(p);

	if (tb[IFLA_BRPORT_COST]) {
		err = br_stp_set_path_cost(p, nla_get_u32(tb[IFLA_BRPORT_COST]));
		if (err)
			return err;
	}

	if (tb[IFLA_BRPORT_PRIORITY]) {
		err = br_stp_set_port_priority(p, nla_get_u16(tb[IFLA_BRPORT_PRIORITY]));
		if (err)
			return err;
	}

	if (tb[IFLA_BRPORT_STATE]) {
		err = br_set_port_state(p, nla_get_u8(tb[IFLA_BRPORT_STATE]));
		if (err)
			return err;
	}

	if (tb[IFLA_BRPORT_FLUSH])
		br_fdb_delete_by_port(p->br, p, 0, 0);

#ifdef CONFIG_BRIDGE_IGMP_SNOOPING
	if (tb[IFLA_BRPORT_MULTICAST_ROUTER]) {
		u8 mcast_router = nla_get_u8(tb[IFLA_BRPORT_MULTICAST_ROUTER]);

		err = br_multicast_set_port_router(p, mcast_router);
		if (err)
			return err;
	}
#endif

	if (tb[IFLA_BRPORT_GROUP_FWD_MASK]) {
		u16 fwd_mask = nla_get_u16(tb[IFLA_BRPORT_GROUP_FWD_MASK]);

		if (fwd_mask & BR_GROUPFWD_MACPAUSE)
			return -EINVAL;
		p->group_fwd_mask = fwd_mask;
	}

	err = br_set_port_flag(p, tb, IFLA_BRPORT_NEIGH_SUPPRESS,
			       BR_NEIGH_SUPPRESS);
	if (err)
		return err;

	err = br_set_port_flag(p, tb, IFLA_BRPORT_ISOLATED, BR_ISOLATED);
	if (err)
		return err;

	if (tb[IFLA_BRPORT_BACKUP_PORT]) {
		struct net_device *backup_dev = NULL;
		u32 backup_ifindex;

		backup_ifindex = nla_get_u32(tb[IFLA_BRPORT_BACKUP_PORT]);
		if (backup_ifindex) {
			backup_dev = __dev_get_by_index(dev_net(p->dev),
							backup_ifindex);
			if (!backup_dev)
				return -ENOENT;
		}

		err = nbp_backup_change(p, backup_dev);
		if (err)
			return err;
	}

	br_port_flags_change(p, old_flags ^ p->flags);
	return 0;
}