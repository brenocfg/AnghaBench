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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; scalar_t__ last_seen; } ;
struct batadv_neigh_node {struct batadv_hard_iface* if_incoming; int /*<<< orphan*/  addr; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct TYPE_2__ {unsigned int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_FLAG_BEST ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_LAST_SEEN_MSECS ; 
 int /*<<< orphan*/  BATADV_ATTR_NEIGH_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_ORIG_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_TQ ; 
 int /*<<< orphan*/  BATADV_CMD_GET_ORIGINATORS ; 
 struct batadv_hard_iface* BATADV_IF_DEFAULT ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  batadv_iv_ogm_neigh_get_tq_avg (struct batadv_neigh_node*,struct batadv_hard_iface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_iv_ogm_orig_dump_subentry(struct sk_buff *msg, u32 portid, u32 seq,
				 struct batadv_priv *bat_priv,
				 struct batadv_hard_iface *if_outgoing,
				 struct batadv_orig_node *orig_node,
				 struct batadv_neigh_node *neigh_node,
				 bool best)
{
	void *hdr;
	u8 tq_avg;
	unsigned int last_seen_msecs;

	last_seen_msecs = jiffies_to_msecs(jiffies - orig_node->last_seen);

	if (!batadv_iv_ogm_neigh_get_tq_avg(neigh_node, if_outgoing, &tq_avg))
		return 0;

	if (if_outgoing != BATADV_IF_DEFAULT &&
	    if_outgoing != neigh_node->if_incoming)
		return 0;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family,
			  NLM_F_MULTI, BATADV_CMD_GET_ORIGINATORS);
	if (!hdr)
		return -ENOBUFS;

	if (nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN,
		    orig_node->orig) ||
	    nla_put(msg, BATADV_ATTR_NEIGH_ADDRESS, ETH_ALEN,
		    neigh_node->addr) ||
	    nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			neigh_node->if_incoming->net_dev->ifindex) ||
	    nla_put_u8(msg, BATADV_ATTR_TQ, tq_avg) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS,
			last_seen_msecs))
		goto nla_put_failure;

	if (best && nla_put_flag(msg, BATADV_ATTR_FLAG_BEST))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}