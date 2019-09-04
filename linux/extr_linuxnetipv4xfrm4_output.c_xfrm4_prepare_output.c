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
struct xfrm_state {TYPE_1__* outer_mode; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int (* output2 ) (struct xfrm_state*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 TYPE_2__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSKB_XFRM_TUNNEL_SIZE ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int stub1 (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm_inner_extract_output (struct xfrm_state*,struct sk_buff*) ; 

int xfrm4_prepare_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;

	err = xfrm_inner_extract_output(x, skb);
	if (err)
		return err;

	IPCB(skb)->flags |= IPSKB_XFRM_TUNNEL_SIZE;
	skb->protocol = htons(ETH_P_IP);

	return x->outer_mode->output2(x, skb);
}