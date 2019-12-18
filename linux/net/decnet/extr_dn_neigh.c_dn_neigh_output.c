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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct neighbour {int /*<<< orphan*/  ha; int /*<<< orphan*/  ha_lock; struct net_device* dev; } ;
struct dst_entry {int dummy; } ;
struct dn_route {int /*<<< orphan*/  rt_local_src; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  dn_dn2eth (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int dn_neigh_output(struct neighbour *neigh, struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct dn_route *rt = (struct dn_route *)dst;
	struct net_device *dev = neigh->dev;
	char mac_addr[ETH_ALEN];
	unsigned int seq;
	int err;

	dn_dn2eth(mac_addr, rt->rt_local_src);
	do {
		seq = read_seqbegin(&neigh->ha_lock);
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
				      neigh->ha, mac_addr, skb->len);
	} while (read_seqretry(&neigh->ha_lock, seq));

	if (err >= 0)
		err = dev_queue_xmit(skb);
	else {
		kfree_skb(skb);
		err = -EINVAL;
	}
	return err;
}