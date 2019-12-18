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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct batadv_softif_vlan {int vid; int /*<<< orphan*/  ap_isolation; } ;
struct batadv_priv {TYPE_1__* soft_iface; } ;
typedef  enum batadv_nl_commands { ____Placeholder_batadv_nl_commands } batadv_nl_commands ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_AP_ISOLATION_ENABLED ; 
 int /*<<< orphan*/  BATADV_ATTR_MESH_IFINDEX ; 
 int /*<<< orphan*/  BATADV_ATTR_VLANID ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int batadv_netlink_vlan_fill(struct sk_buff *msg,
				    struct batadv_priv *bat_priv,
				    struct batadv_softif_vlan *vlan,
				    enum batadv_nl_commands cmd,
				    u32 portid, u32 seq, int flags)
{
	void *hdr;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family, flags, cmd);
	if (!hdr)
		return -ENOBUFS;

	if (nla_put_u32(msg, BATADV_ATTR_MESH_IFINDEX,
			bat_priv->soft_iface->ifindex))
		goto nla_put_failure;

	if (nla_put_u32(msg, BATADV_ATTR_VLANID, vlan->vid & VLAN_VID_MASK))
		goto nla_put_failure;

	if (nla_put_u8(msg, BATADV_ATTR_AP_ISOLATION_ENABLED,
		       !!atomic_read(&vlan->ap_isolation)))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}