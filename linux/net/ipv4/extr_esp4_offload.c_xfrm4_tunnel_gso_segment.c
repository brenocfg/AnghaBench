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
struct xfrm_state {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mac_len; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_mac_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *xfrm4_tunnel_gso_segment(struct xfrm_state *x,
						struct sk_buff *skb,
						netdev_features_t features)
{
	__skb_push(skb, skb->mac_len);
	return skb_mac_gso_segment(skb, features);
}