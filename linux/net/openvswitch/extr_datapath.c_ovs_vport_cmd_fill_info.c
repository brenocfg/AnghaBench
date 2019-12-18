#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vport {TYPE_2__* dev; TYPE_1__* ops; int /*<<< orphan*/  port_no; int /*<<< orphan*/  dp; } ;
struct sk_buff {int dummy; } ;
struct ovs_vport_stats {int dummy; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_IFINDEX ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_NAME ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_NETNSID ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_PAD ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_PORT_NO ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_STATS ; 
 int /*<<< orphan*/  OVS_VPORT_ATTR_TYPE ; 
 int /*<<< orphan*/  dev_net (TYPE_2__*) ; 
 int /*<<< orphan*/  dp_vport_genl_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,struct ovs_header*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,struct ovs_header*) ; 
 struct ovs_header* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dpifindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct ovs_vport_stats*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovs_vport_get_options (struct vport*,struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_vport_get_stats (struct vport*,struct ovs_vport_stats*) ; 
 scalar_t__ ovs_vport_get_upcall_portids (struct vport*,struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_vport_name (struct vport*) ; 
 int peernet2id_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_vport_cmd_fill_info(struct vport *vport, struct sk_buff *skb,
				   struct net *net, u32 portid, u32 seq,
				   u32 flags, u8 cmd, gfp_t gfp)
{
	struct ovs_header *ovs_header;
	struct ovs_vport_stats vport_stats;
	int err;

	ovs_header = genlmsg_put(skb, portid, seq, &dp_vport_genl_family,
				 flags, cmd);
	if (!ovs_header)
		return -EMSGSIZE;

	ovs_header->dp_ifindex = get_dpifindex(vport->dp);

	if (nla_put_u32(skb, OVS_VPORT_ATTR_PORT_NO, vport->port_no) ||
	    nla_put_u32(skb, OVS_VPORT_ATTR_TYPE, vport->ops->type) ||
	    nla_put_string(skb, OVS_VPORT_ATTR_NAME,
			   ovs_vport_name(vport)) ||
	    nla_put_u32(skb, OVS_VPORT_ATTR_IFINDEX, vport->dev->ifindex))
		goto nla_put_failure;

	if (!net_eq(net, dev_net(vport->dev))) {
		int id = peernet2id_alloc(net, dev_net(vport->dev), gfp);

		if (nla_put_s32(skb, OVS_VPORT_ATTR_NETNSID, id))
			goto nla_put_failure;
	}

	ovs_vport_get_stats(vport, &vport_stats);
	if (nla_put_64bit(skb, OVS_VPORT_ATTR_STATS,
			  sizeof(struct ovs_vport_stats), &vport_stats,
			  OVS_VPORT_ATTR_PAD))
		goto nla_put_failure;

	if (ovs_vport_get_upcall_portids(vport, skb))
		goto nla_put_failure;

	err = ovs_vport_get_options(vport, skb);
	if (err == -EMSGSIZE)
		goto error;

	genlmsg_end(skb, ovs_header);
	return 0;

nla_put_failure:
	err = -EMSGSIZE;
error:
	genlmsg_cancel(skb, ovs_header);
	return err;
}