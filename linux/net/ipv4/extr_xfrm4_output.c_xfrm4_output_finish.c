#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSKB_XFRM_TRANSFORMED ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int xfrm_output (struct sock*,struct sk_buff*) ; 

int xfrm4_output_finish(struct sock *sk, struct sk_buff *skb)
{
	memset(IPCB(skb), 0, sizeof(*IPCB(skb)));

#ifdef CONFIG_NETFILTER
	IPCB(skb)->flags |= IPSKB_XFRM_TRANSFORMED;
#endif

	return xfrm_output(sk, skb);
}