#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct rtmsg {int rtm_flags; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct dn_route {int /*<<< orphan*/  dst; int /*<<< orphan*/  dn_next; } ;
struct TYPE_7__ {int /*<<< orphan*/  portid; } ;
struct TYPE_6__ {int /*<<< orphan*/  chain; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_4__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int RTM_F_CLONED ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 scalar_t__ dn_rt_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dn_rt_hash_mask ; 
 TYPE_3__* dn_rt_hash_table ; 
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 struct rtmsg* nlmsg_data (TYPE_1__*) ; 
 int nlmsg_len (TYPE_1__*) ; 
 struct dn_route* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int dn_cache_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct dn_route *rt;
	int h, s_h;
	int idx, s_idx;
	struct rtmsg *rtm;

	if (!net_eq(net, &init_net))
		return 0;

	if (nlmsg_len(cb->nlh) < sizeof(struct rtmsg))
		return -EINVAL;

	rtm = nlmsg_data(cb->nlh);
	if (!(rtm->rtm_flags & RTM_F_CLONED))
		return 0;

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];
	for(h = 0; h <= dn_rt_hash_mask; h++) {
		if (h < s_h)
			continue;
		if (h > s_h)
			s_idx = 0;
		rcu_read_lock_bh();
		for(rt = rcu_dereference_bh(dn_rt_hash_table[h].chain), idx = 0;
			rt;
			rt = rcu_dereference_bh(rt->dn_next), idx++) {
			if (idx < s_idx)
				continue;
			skb_dst_set(skb, dst_clone(&rt->dst));
			if (dn_rt_fill_info(skb, NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq, RTM_NEWROUTE,
					1, NLM_F_MULTI) < 0) {
				skb_dst_drop(skb);
				rcu_read_unlock_bh();
				goto done;
			}
			skb_dst_drop(skb);
		}
		rcu_read_unlock_bh();
	}

done:
	cb->args[0] = h;
	cb->args[1] = idx;
	return skb->len;
}