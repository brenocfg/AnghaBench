#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ family; } ;
struct xfrm_state {TYPE_4__ sel; TYPE_3__* outer_mode; struct xfrm_mode* inner_mode; } ;
struct xfrm_mode {int (* input2 ) (struct xfrm_state*,struct sk_buff*) ;TYPE_1__* afinfo; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_10__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_8__ {TYPE_2__* afinfo; } ;
struct TYPE_7__ {int (* extract_input ) (struct xfrm_state*,struct sk_buff*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  eth_proto; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EAFNOSUPPORT ; 
 TYPE_5__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int stub1 (struct xfrm_state*,struct sk_buff*) ; 
 int stub2 (struct xfrm_state*,struct sk_buff*) ; 
 struct xfrm_mode* xfrm_ip2inner_mode (struct xfrm_state*,int /*<<< orphan*/ ) ; 

int xfrm_prepare_input(struct xfrm_state *x, struct sk_buff *skb)
{
	struct xfrm_mode *inner_mode = x->inner_mode;
	int err;

	err = x->outer_mode->afinfo->extract_input(x, skb);
	if (err)
		return err;

	if (x->sel.family == AF_UNSPEC) {
		inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
		if (inner_mode == NULL)
			return -EAFNOSUPPORT;
	}

	skb->protocol = inner_mode->afinfo->eth_proto;
	return inner_mode->input2(x, skb);
}