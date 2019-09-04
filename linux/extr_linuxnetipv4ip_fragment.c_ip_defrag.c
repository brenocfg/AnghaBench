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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ipq {TYPE_1__ q; } ;
struct TYPE_4__ {struct net_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMREQDS ; 
 int /*<<< orphan*/  __IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct ipq* ip_find (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ip_frag_queue (struct ipq*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipq_put (struct ipq*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int l3mdev_master_ifindex_rcu (struct net_device*) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ip_defrag(struct net *net, struct sk_buff *skb, u32 user)
{
	struct net_device *dev = skb->dev ? : skb_dst(skb)->dev;
	int vif = l3mdev_master_ifindex_rcu(dev);
	struct ipq *qp;

	__IP_INC_STATS(net, IPSTATS_MIB_REASMREQDS);
	skb_orphan(skb);

	/* Lookup (or create) queue header */
	qp = ip_find(net, ip_hdr(skb), user, vif);
	if (qp) {
		int ret;

		spin_lock(&qp->q.lock);

		ret = ip_frag_queue(qp, skb);

		spin_unlock(&qp->q.lock);
		ipq_put(qp);
		return ret;
	}

	__IP_INC_STATS(net, IPSTATS_MIB_REASMFAILS);
	kfree_skb(skb);
	return -ENOMEM;
}