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
struct genl_info {int /*<<< orphan*/  snd_portid; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t L2TP_ATTR_CONN_ID ; 
 int /*<<< orphan*/  L2TP_CMD_TUNNEL_GET ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  NLM_F_ACK ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int genlmsg_unicast (struct net*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int l2tp_nl_tunnel_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct l2tp_tunnel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_tunnel_dec_refcount (struct l2tp_tunnel*) ; 
 struct l2tp_tunnel* l2tp_tunnel_get (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2tp_nl_cmd_tunnel_get(struct sk_buff *skb, struct genl_info *info)
{
	struct l2tp_tunnel *tunnel;
	struct sk_buff *msg;
	u32 tunnel_id;
	int ret = -ENOBUFS;
	struct net *net = genl_info_net(info);

	if (!info->attrs[L2TP_ATTR_CONN_ID]) {
		ret = -EINVAL;
		goto err;
	}

	tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg) {
		ret = -ENOMEM;
		goto err;
	}

	tunnel = l2tp_tunnel_get(net, tunnel_id);
	if (!tunnel) {
		ret = -ENODEV;
		goto err_nlmsg;
	}

	ret = l2tp_nl_tunnel_send(msg, info->snd_portid, info->snd_seq,
				  NLM_F_ACK, tunnel, L2TP_CMD_TUNNEL_GET);
	if (ret < 0)
		goto err_nlmsg_tunnel;

	l2tp_tunnel_dec_refcount(tunnel);

	return genlmsg_unicast(net, msg, info->snd_portid);

err_nlmsg_tunnel:
	l2tp_tunnel_dec_refcount(tunnel);
err_nlmsg:
	nlmsg_free(msg);
err:
	return ret;
}