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
struct xfrm_state {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct xfrm_state* xfrm; } ;

/* Variables and functions */
 int __xfrm6_output_state_finish (struct xfrm_state*,struct sock*,struct sk_buff*) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int __xfrm6_output_finish(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct xfrm_state *x = skb_dst(skb)->xfrm;

	return __xfrm6_output_state_finish(x, sk, skb);
}