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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ovs_conntrack_info {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static inline int ovs_ct_execute(struct net *net, struct sk_buff *skb,
				 struct sw_flow_key *key,
				 const struct ovs_conntrack_info *info)
{
	kfree_skb(skb);
	return -ENOTSUPP;
}