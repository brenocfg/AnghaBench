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
struct net {int dummy; } ;
struct l2tp_tunnel {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t L2TP_ATTR_CONN_ID ; 
 int /*<<< orphan*/  L2TP_CMD_TUNNEL_DELETE ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  l2tp_nl_family ; 
 int /*<<< orphan*/  l2tp_tunnel_dec_refcount (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  l2tp_tunnel_delete (struct l2tp_tunnel*) ; 
 struct l2tp_tunnel* l2tp_tunnel_get (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_tunnel_notify (int /*<<< orphan*/ *,struct genl_info*,struct l2tp_tunnel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2tp_nl_cmd_tunnel_delete(struct sk_buff *skb, struct genl_info *info)
{
	struct l2tp_tunnel *tunnel;
	u32 tunnel_id;
	int ret = 0;
	struct net *net = genl_info_net(info);

	if (!info->attrs[L2TP_ATTR_CONN_ID]) {
		ret = -EINVAL;
		goto out;
	}
	tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);

	tunnel = l2tp_tunnel_get(net, tunnel_id);
	if (!tunnel) {
		ret = -ENODEV;
		goto out;
	}

	l2tp_tunnel_notify(&l2tp_nl_family, info,
			   tunnel, L2TP_CMD_TUNNEL_DELETE);

	l2tp_tunnel_delete(tunnel);

	l2tp_tunnel_dec_refcount(tunnel);

out:
	return ret;
}