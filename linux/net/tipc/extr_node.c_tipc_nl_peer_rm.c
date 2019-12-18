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
struct tipc_node {scalar_t__ state; } ;
struct tipc_net {int /*<<< orphan*/  node_list_lock; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int ENXIO ; 
 scalar_t__ SELF_DOWN_PEER_DOWN ; 
 scalar_t__ SELF_DOWN_PEER_LEAVING ; 
 size_t TIPC_NLA_NET ; 
 size_t TIPC_NLA_NET_ADDR ; 
 int /*<<< orphan*/  TIPC_NLA_NET_MAX ; 
 scalar_t__ in_own_node (struct net*,int /*<<< orphan*/ ) ; 
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_id ; 
 int /*<<< orphan*/  tipc_nl_net_policy ; 
 int /*<<< orphan*/  tipc_node_clear_links (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_delete (struct tipc_node*) ; 
 struct tipc_node* tipc_node_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_unlock (struct tipc_node*) ; 

int tipc_nl_peer_rm(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = sock_net(skb->sk);
	struct tipc_net *tn = net_generic(net, tipc_net_id);
	struct nlattr *attrs[TIPC_NLA_NET_MAX + 1];
	struct tipc_node *peer;
	u32 addr;
	int err;

	/* We identify the peer by its net */
	if (!info->attrs[TIPC_NLA_NET])
		return -EINVAL;

	err = nla_parse_nested_deprecated(attrs, TIPC_NLA_NET_MAX,
					  info->attrs[TIPC_NLA_NET],
					  tipc_nl_net_policy, info->extack);
	if (err)
		return err;

	if (!attrs[TIPC_NLA_NET_ADDR])
		return -EINVAL;

	addr = nla_get_u32(attrs[TIPC_NLA_NET_ADDR]);

	if (in_own_node(net, addr))
		return -ENOTSUPP;

	spin_lock_bh(&tn->node_list_lock);
	peer = tipc_node_find(net, addr);
	if (!peer) {
		spin_unlock_bh(&tn->node_list_lock);
		return -ENXIO;
	}

	tipc_node_write_lock(peer);
	if (peer->state != SELF_DOWN_PEER_DOWN &&
	    peer->state != SELF_DOWN_PEER_LEAVING) {
		tipc_node_write_unlock(peer);
		err = -EBUSY;
		goto err_out;
	}

	tipc_node_clear_links(peer);
	tipc_node_write_unlock(peer);
	tipc_node_delete(peer);

	err = 0;
err_out:
	tipc_node_put(peer);
	spin_unlock_bh(&tn->node_list_lock);

	return err;
}