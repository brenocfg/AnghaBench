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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct neighbour {int (* output ) (struct neighbour*,struct sk_buff*) ;} ;
struct neigh_table {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int NEIGH_ARP_TABLE ; 
 int NEIGH_LINK_TABLE ; 
 int NEIGH_NR_TABLES ; 
 int PTR_ERR (struct neighbour*) ; 
 struct neighbour* __ipv4_neigh_lookup_noref (struct net_device*,int /*<<< orphan*/ ) ; 
 struct neighbour* __neigh_create (struct neigh_table*,void const*,struct net_device*,int) ; 
 struct neighbour* __neigh_lookup_noref (struct neigh_table*,void const*,struct net_device*) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct neigh_table** neigh_tables ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int stub1 (struct neighbour*,struct sk_buff*) ; 

int neigh_xmit(int index, struct net_device *dev,
	       const void *addr, struct sk_buff *skb)
{
	int err = -EAFNOSUPPORT;
	if (likely(index < NEIGH_NR_TABLES)) {
		struct neigh_table *tbl;
		struct neighbour *neigh;

		tbl = neigh_tables[index];
		if (!tbl)
			goto out;
		rcu_read_lock_bh();
		if (index == NEIGH_ARP_TABLE) {
			u32 key = *((u32 *)addr);

			neigh = __ipv4_neigh_lookup_noref(dev, key);
		} else {
			neigh = __neigh_lookup_noref(tbl, addr, dev);
		}
		if (!neigh)
			neigh = __neigh_create(tbl, addr, dev, false);
		err = PTR_ERR(neigh);
		if (IS_ERR(neigh)) {
			rcu_read_unlock_bh();
			goto out_kfree_skb;
		}
		err = neigh->output(neigh, skb);
		rcu_read_unlock_bh();
	}
	else if (index == NEIGH_LINK_TABLE) {
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
				      addr, NULL, skb->len);
		if (err < 0)
			goto out_kfree_skb;
		err = dev_queue_xmit(skb);
	}
out:
	return err;
out_kfree_skb:
	kfree_skb(skb);
	goto out;
}