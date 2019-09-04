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
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {int* args; struct nlmsghdr* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct neighbour {int /*<<< orphan*/  dev; int /*<<< orphan*/  next; } ;
struct neigh_table {int /*<<< orphan*/  nht; } ;
struct neigh_hash_table {int hash_shift; int /*<<< orphan*/ * hash_buckets; } ;
struct ndmsg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NDA_IFINDEX ; 
 size_t NDA_MASTER ; 
 int /*<<< orphan*/  NDA_MAX ; 
 TYPE_1__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 unsigned int NLM_F_DUMP_FILTERED ; 
 unsigned int NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ neigh_fill_info (struct sk_buff*,struct neighbour*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ neigh_ifindex_filtered (int /*<<< orphan*/ ,int) ; 
 scalar_t__ neigh_master_filtered (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nlmsg_parse (struct nlmsghdr const*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neigh_dump_table(struct neigh_table *tbl, struct sk_buff *skb,
			    struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	const struct nlmsghdr *nlh = cb->nlh;
	struct nlattr *tb[NDA_MAX + 1];
	struct neighbour *n;
	int rc, h, s_h = cb->args[1];
	int idx, s_idx = idx = cb->args[2];
	struct neigh_hash_table *nht;
	int filter_master_idx = 0, filter_idx = 0;
	unsigned int flags = NLM_F_MULTI;
	int err;

	err = nlmsg_parse(nlh, sizeof(struct ndmsg), tb, NDA_MAX, NULL, NULL);
	if (!err) {
		if (tb[NDA_IFINDEX]) {
			if (nla_len(tb[NDA_IFINDEX]) != sizeof(u32))
				return -EINVAL;
			filter_idx = nla_get_u32(tb[NDA_IFINDEX]);
		}
		if (tb[NDA_MASTER]) {
			if (nla_len(tb[NDA_MASTER]) != sizeof(u32))
				return -EINVAL;
			filter_master_idx = nla_get_u32(tb[NDA_MASTER]);
		}
		if (filter_idx || filter_master_idx)
			flags |= NLM_F_DUMP_FILTERED;
	}

	rcu_read_lock_bh();
	nht = rcu_dereference_bh(tbl->nht);

	for (h = s_h; h < (1 << nht->hash_shift); h++) {
		if (h > s_h)
			s_idx = 0;
		for (n = rcu_dereference_bh(nht->hash_buckets[h]), idx = 0;
		     n != NULL;
		     n = rcu_dereference_bh(n->next)) {
			if (idx < s_idx || !net_eq(dev_net(n->dev), net))
				goto next;
			if (neigh_ifindex_filtered(n->dev, filter_idx) ||
			    neigh_master_filtered(n->dev, filter_master_idx))
				goto next;
			if (neigh_fill_info(skb, n, NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    RTM_NEWNEIGH,
					    flags) < 0) {
				rc = -1;
				goto out;
			}
next:
			idx++;
		}
	}
	rc = skb->len;
out:
	rcu_read_unlock_bh();
	cb->args[1] = h;
	cb->args[2] = idx;
	return rc;
}