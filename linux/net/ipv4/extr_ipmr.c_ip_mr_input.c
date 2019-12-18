#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct mr_table {int /*<<< orphan*/  mroute_sk; } ;
struct mfc_cache {int dummy; } ;
struct TYPE_5__ {scalar_t__ router_alert; } ;
struct TYPE_8__ {int flags; TYPE_1__ opt; int /*<<< orphan*/  iif; } ;
struct TYPE_7__ {scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {int rt_flags; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_4__* IPCB (struct sk_buff*) ; 
 scalar_t__ IPPROTO_IGMP ; 
 int IPSKB_FORWARDED ; 
 scalar_t__ IS_ERR (struct mr_table*) ; 
 int PTR_ERR (struct mr_table*) ; 
 int RTCF_LOCAL ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 scalar_t__ ip_call_ra_chain (struct sk_buff*) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int ip_local_deliver (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_mr_forward (struct net*,struct mr_table*,struct net_device*,struct sk_buff*,struct mfc_cache*,int) ; 
 struct mfc_cache* ipmr_cache_find (struct mr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mfc_cache* ipmr_cache_find_any (struct mr_table*,int /*<<< orphan*/ ,int) ; 
 int ipmr_cache_unresolved (struct mr_table*,int,struct sk_buff*,struct net_device*) ; 
 int ipmr_find_vif (struct mr_table*,struct net_device*) ; 
 struct mr_table* ipmr_rt_fib_lookup (struct net*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mrt_lock ; 
 scalar_t__ netif_is_l3_master (struct net_device*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  raw_rcv (struct sock*,struct sk_buff*) ; 
 struct sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_rtable (struct sk_buff*) ; 

int ip_mr_input(struct sk_buff *skb)
{
	struct mfc_cache *cache;
	struct net *net = dev_net(skb->dev);
	int local = skb_rtable(skb)->rt_flags & RTCF_LOCAL;
	struct mr_table *mrt;
	struct net_device *dev;

	/* skb->dev passed in is the loX master dev for vrfs.
	 * As there are no vifs associated with loopback devices,
	 * get the proper interface that does have a vif associated with it.
	 */
	dev = skb->dev;
	if (netif_is_l3_master(skb->dev)) {
		dev = dev_get_by_index_rcu(net, IPCB(skb)->iif);
		if (!dev) {
			kfree_skb(skb);
			return -ENODEV;
		}
	}

	/* Packet is looped back after forward, it should not be
	 * forwarded second time, but still can be delivered locally.
	 */
	if (IPCB(skb)->flags & IPSKB_FORWARDED)
		goto dont_forward;

	mrt = ipmr_rt_fib_lookup(net, skb);
	if (IS_ERR(mrt)) {
		kfree_skb(skb);
		return PTR_ERR(mrt);
	}
	if (!local) {
		if (IPCB(skb)->opt.router_alert) {
			if (ip_call_ra_chain(skb))
				return 0;
		} else if (ip_hdr(skb)->protocol == IPPROTO_IGMP) {
			/* IGMPv1 (and broken IGMPv2 implementations sort of
			 * Cisco IOS <= 11.2(8)) do not put router alert
			 * option to IGMP packets destined to routable
			 * groups. It is very bad, because it means
			 * that we can forward NO IGMP messages.
			 */
			struct sock *mroute_sk;

			mroute_sk = rcu_dereference(mrt->mroute_sk);
			if (mroute_sk) {
				nf_reset_ct(skb);
				raw_rcv(mroute_sk, skb);
				return 0;
			}
		    }
	}

	/* already under rcu_read_lock() */
	cache = ipmr_cache_find(mrt, ip_hdr(skb)->saddr, ip_hdr(skb)->daddr);
	if (!cache) {
		int vif = ipmr_find_vif(mrt, dev);

		if (vif >= 0)
			cache = ipmr_cache_find_any(mrt, ip_hdr(skb)->daddr,
						    vif);
	}

	/* No usable cache entry */
	if (!cache) {
		int vif;

		if (local) {
			struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
			ip_local_deliver(skb);
			if (!skb2)
				return -ENOBUFS;
			skb = skb2;
		}

		read_lock(&mrt_lock);
		vif = ipmr_find_vif(mrt, dev);
		if (vif >= 0) {
			int err2 = ipmr_cache_unresolved(mrt, vif, skb, dev);
			read_unlock(&mrt_lock);

			return err2;
		}
		read_unlock(&mrt_lock);
		kfree_skb(skb);
		return -ENODEV;
	}

	read_lock(&mrt_lock);
	ip_mr_forward(net, mrt, dev, skb, cache, local);
	read_unlock(&mrt_lock);

	if (local)
		return ip_local_deliver(skb);

	return 0;

dont_forward:
	if (local)
		return ip_local_deliver(skb);
	kfree_skb(skb);
	return 0;
}