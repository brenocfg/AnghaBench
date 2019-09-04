#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfrm_state {TYPE_2__* outer_mode; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_6__ {struct xfrm_state* xfrm; } ;
struct TYPE_5__ {TYPE_1__* afinfo; } ;
struct TYPE_4__ {int (* output_finish ) (struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 int stub1 (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int __xfrm4_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct xfrm_state *x = skb_dst(skb)->xfrm;

#ifdef CONFIG_NETFILTER
	if (!x) {
		IPCB(skb)->flags |= IPSKB_REROUTED;
		return dst_output(net, sk, skb);
	}
#endif

	return x->outer_mode->afinfo->output_finish(sk, skb);
}