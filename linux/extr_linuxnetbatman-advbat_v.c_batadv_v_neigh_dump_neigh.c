#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  throughput; } ;
struct batadv_hardif_neigh_node {TYPE_3__* if_incoming; int /*<<< orphan*/  addr; TYPE_1__ bat_v; scalar_t__ last_seen; } ;
struct TYPE_6__ {TYPE_2__* net_dev; } ;
struct TYPE_5__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_LAST_SEEN_MSECS ; 
 int /*<<< orphan*/  BATADV_ATTR_NEIGH_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_THROUGHPUT ; 
 int /*<<< orphan*/  BATADV_CMD_GET_NEIGHBORS ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int ewma_throughput_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
batadv_v_neigh_dump_neigh(struct sk_buff *msg, u32 portid, u32 seq,
			  struct batadv_hardif_neigh_node *hardif_neigh)
{
	void *hdr;
	unsigned int last_seen_msecs;
	u32 throughput;

	last_seen_msecs = jiffies_to_msecs(jiffies - hardif_neigh->last_seen);
	throughput = ewma_throughput_read(&hardif_neigh->bat_v.throughput);
	throughput = throughput * 100;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_NEIGHBORS);
	if (!hdr)
		return -ENOBUFS;

	if (nla_put(msg, BATADV_ATTR_NEIGH_ADDRESS, ETH_ALEN,
		    hardif_neigh->addr) ||
	    nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			hardif_neigh->if_incoming->net_dev->ifindex) ||
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS,
			last_seen_msecs) ||
	    nla_put_u32(msg, BATADV_ATTR_THROUGHPUT, throughput))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}