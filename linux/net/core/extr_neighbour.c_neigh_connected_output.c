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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 

int neigh_connected_output(struct neighbour *neigh, struct sk_buff *skb)
{
	struct net_device *dev = neigh->dev;
	unsigned int seq;
	int err;

	do {
		__skb_pull(skb, skb_network_offset(skb));
		seq = read_seqbegin(&neigh->ha_lock);
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
				      neigh->ha, NULL, skb->len);
	} while (read_seqretry(&neigh->ha_lock, seq));

	if (err >= 0)
		err = dev_queue_xmit(skb);
	else {
		err = -EINVAL;
		kfree_skb(skb);
	}
	return err;
}