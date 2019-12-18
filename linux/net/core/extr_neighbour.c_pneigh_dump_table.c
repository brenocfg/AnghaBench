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
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct pneigh_entry {int /*<<< orphan*/  dev; struct pneigh_entry* next; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct neigh_table {int /*<<< orphan*/  lock; struct pneigh_entry** phash_buckets; } ;
struct neigh_dump_filter {int /*<<< orphan*/  master_idx; int /*<<< orphan*/  dev_idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 unsigned int NLM_F_DUMP_FILTERED ; 
 unsigned int NLM_F_MULTI ; 
 int PNEIGH_HASHMASK ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 scalar_t__ neigh_ifindex_filtered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ neigh_master_filtered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pneigh_fill_info (struct sk_buff*,struct pneigh_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct neigh_table*) ; 
 struct net* pneigh_net (struct pneigh_entry*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pneigh_dump_table(struct neigh_table *tbl, struct sk_buff *skb,
			     struct netlink_callback *cb,
			     struct neigh_dump_filter *filter)
{
	struct pneigh_entry *n;
	struct net *net = sock_net(skb->sk);
	int rc, h, s_h = cb->args[3];
	int idx, s_idx = idx = cb->args[4];
	unsigned int flags = NLM_F_MULTI;

	if (filter->dev_idx || filter->master_idx)
		flags |= NLM_F_DUMP_FILTERED;

	read_lock_bh(&tbl->lock);

	for (h = s_h; h <= PNEIGH_HASHMASK; h++) {
		if (h > s_h)
			s_idx = 0;
		for (n = tbl->phash_buckets[h], idx = 0; n; n = n->next) {
			if (idx < s_idx || pneigh_net(n) != net)
				goto next;
			if (neigh_ifindex_filtered(n->dev, filter->dev_idx) ||
			    neigh_master_filtered(n->dev, filter->master_idx))
				goto next;
			if (pneigh_fill_info(skb, n, NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    RTM_NEWNEIGH, flags, tbl) < 0) {
				read_unlock_bh(&tbl->lock);
				rc = -1;
				goto out;
			}
		next:
			idx++;
		}
	}

	read_unlock_bh(&tbl->lock);
	rc = skb->len;
out:
	cb->args[3] = h;
	cb->args[4] = idx;
	return rc;

}