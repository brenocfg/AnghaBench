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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct bpf_redirect_info {int /*<<< orphan*/  flags; scalar_t__ tgt_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int __bpf_redirect (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_redirect_info ; 
 struct net_device* dev_get_by_index_rcu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct bpf_redirect_info* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int skb_do_redirect(struct sk_buff *skb)
{
	struct bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	struct net_device *dev;

	dev = dev_get_by_index_rcu(dev_net(skb->dev), ri->tgt_index);
	ri->tgt_index = 0;
	if (unlikely(!dev)) {
		kfree_skb(skb);
		return -EINVAL;
	}

	return __bpf_redirect(skb, dev, ri->flags);
}