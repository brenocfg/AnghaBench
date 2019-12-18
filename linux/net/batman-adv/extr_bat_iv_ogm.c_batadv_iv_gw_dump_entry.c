#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct netlink_callback {TYPE_1__* nlh; } ;
struct batadv_priv {int dummy; } ;
struct batadv_neigh_node {TYPE_4__* if_incoming; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  tq_avg; } ;
struct batadv_neigh_ifinfo {TYPE_2__ bat_iv; } ;
struct batadv_gw_node {int /*<<< orphan*/  bandwidth_up; int /*<<< orphan*/  bandwidth_down; TYPE_5__* orig_node; } ;
struct TYPE_10__ {int /*<<< orphan*/  orig; } ;
struct TYPE_9__ {TYPE_3__* net_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_BANDWIDTH_DOWN ; 
 int /*<<< orphan*/  BATADV_ATTR_BANDWIDTH_UP ; 
 int /*<<< orphan*/  BATADV_ATTR_FLAG_BEST ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFNAME ; 
 int /*<<< orphan*/  BATADV_ATTR_ORIG_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_ROUTER ; 
 int /*<<< orphan*/  BATADV_ATTR_TQ ; 
 int /*<<< orphan*/  BATADV_CMD_GET_GATEWAYS ; 
 int /*<<< orphan*/  BATADV_IF_DEFAULT ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 struct batadv_gw_node* batadv_gw_get_selected_gw_node (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_gw_node_put (struct batadv_gw_node*) ; 
 struct batadv_neigh_ifinfo* batadv_neigh_ifinfo_get (struct batadv_neigh_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_neigh_ifinfo_put (struct batadv_neigh_ifinfo*) ; 
 int /*<<< orphan*/  batadv_neigh_node_put (struct batadv_neigh_node*) ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 struct batadv_neigh_node* batadv_orig_router_get (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_dump_check_consistent (struct netlink_callback*,void*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_iv_gw_dump_entry(struct sk_buff *msg, u32 portid,
				   struct netlink_callback *cb,
				   struct batadv_priv *bat_priv,
				   struct batadv_gw_node *gw_node)
{
	struct batadv_neigh_ifinfo *router_ifinfo = NULL;
	struct batadv_neigh_node *router;
	struct batadv_gw_node *curr_gw = NULL;
	int ret = 0;
	void *hdr;

	router = batadv_orig_router_get(gw_node->orig_node, BATADV_IF_DEFAULT);
	if (!router)
		goto out;

	router_ifinfo = batadv_neigh_ifinfo_get(router, BATADV_IF_DEFAULT);
	if (!router_ifinfo)
		goto out;

	curr_gw = batadv_gw_get_selected_gw_node(bat_priv);

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_GATEWAYS);
	if (!hdr) {
		ret = -ENOBUFS;
		goto out;
	}

	genl_dump_check_consistent(cb, hdr);

	ret = -EMSGSIZE;

	if (curr_gw == gw_node)
		if (nla_put_flag(msg, BATADV_ATTR_FLAG_BEST)) {
			genlmsg_cancel(msg, hdr);
			goto out;
		}

	if (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN,
		    gw_node->orig_node->orig) ||
	    nla_put_u8(msg, BATADV_ATTR_TQ, router_ifinfo->bat_iv.tq_avg) ||
	    nla_put(msg, BATADV_ATTR_ROUTER, ETH_ALEN,
		    router->addr) ||
	    nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
			   router->if_incoming->net_dev->name) ||
	    nla_put_u32(msg, BATADV_ATTR_BANDWIDTH_DOWN,
			gw_node->bandwidth_down) ||
	    nla_put_u32(msg, BATADV_ATTR_BANDWIDTH_UP,
			gw_node->bandwidth_up)) {
		genlmsg_cancel(msg, hdr);
		goto out;
	}

	genlmsg_end(msg, hdr);
	ret = 0;

out:
	if (curr_gw)
		batadv_gw_node_put(curr_gw);
	if (router_ifinfo)
		batadv_neigh_ifinfo_put(router_ifinfo);
	if (router)
		batadv_neigh_node_put(router);
	return ret;
}