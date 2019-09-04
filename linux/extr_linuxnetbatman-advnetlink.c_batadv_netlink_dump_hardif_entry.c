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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct batadv_hard_iface {scalar_t__ if_status; struct net_device* net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_ACTIVE ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_ADDRESS ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_HARD_IFNAME ; 
 int /*<<< orphan*/  BATADV_CMD_GET_HARDIFS ; 
 scalar_t__ BATADV_IF_ACTIVE ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
batadv_netlink_dump_hardif_entry(struct sk_buff *msg, u32 portid, u32 seq,
				 struct batadv_hard_iface *hard_iface)
{
	struct net_device *net_dev = hard_iface->net_dev;
	void *hdr;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, NLM_F_MULTI,
			  BATADV_CMD_GET_HARDIFS);
	if (!hdr)
		return -EMSGSIZE;

	if (nla_put_u32(msg, BATADV_ATTR_HARD_IFINDEX,
			net_dev->ifindex) ||
	    nla_put_string(msg, BATADV_ATTR_HARD_IFNAME,
			   net_dev->name) ||
	    nla_put(msg, BATADV_ATTR_HARD_ADDRESS, ETH_ALEN,
		    net_dev->dev_addr))
		goto nla_put_failure;

	if (hard_iface->if_status == BATADV_IF_ACTIVE) {
		if (nla_put_flag(msg, BATADV_ATTR_ACTIVE))
			goto nla_put_failure;
	}

	genlmsg_end(msg, hdr);
	return 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}