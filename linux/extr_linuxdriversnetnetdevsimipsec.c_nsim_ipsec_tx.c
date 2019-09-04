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
typedef  size_t u32 ;
struct TYPE_6__ {size_t proto; } ;
struct TYPE_5__ {size_t offload_handle; } ;
struct xfrm_state {TYPE_3__ id; TYPE_2__ xso; } ;
struct sk_buff {TYPE_1__* sp; } ;
struct nsim_sa {int /*<<< orphan*/  used; } ;
struct nsim_ipsec {int /*<<< orphan*/  tx; struct nsim_sa* sa; } ;
struct netdevsim {int /*<<< orphan*/  netdev; struct nsim_ipsec ipsec; } ;
struct TYPE_4__ {size_t len; } ;

/* Variables and functions */
 size_t IPPROTO_AH ; 
 size_t IPPROTO_ESP ; 
 size_t NSIM_IPSEC_MAX_SA_COUNT ; 
 size_t NSIM_IPSEC_VALID ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 

bool nsim_ipsec_tx(struct netdevsim *ns, struct sk_buff *skb)
{
	struct nsim_ipsec *ipsec = &ns->ipsec;
	struct xfrm_state *xs;
	struct nsim_sa *tsa;
	u32 sa_idx;

	/* do we even need to check this packet? */
	if (!skb->sp)
		return true;

	if (unlikely(!skb->sp->len)) {
		netdev_err(ns->netdev, "no xfrm state len = %d\n",
			   skb->sp->len);
		return false;
	}

	xs = xfrm_input_state(skb);
	if (unlikely(!xs)) {
		netdev_err(ns->netdev, "no xfrm_input_state() xs = %p\n", xs);
		return false;
	}

	sa_idx = xs->xso.offload_handle & ~NSIM_IPSEC_VALID;
	if (unlikely(sa_idx >= NSIM_IPSEC_MAX_SA_COUNT)) {
		netdev_err(ns->netdev, "bad sa_idx=%d max=%d\n",
			   sa_idx, NSIM_IPSEC_MAX_SA_COUNT);
		return false;
	}

	tsa = &ipsec->sa[sa_idx];
	if (unlikely(!tsa->used)) {
		netdev_err(ns->netdev, "unused sa_idx=%d\n", sa_idx);
		return false;
	}

	if (xs->id.proto != IPPROTO_ESP && xs->id.proto != IPPROTO_AH) {
		netdev_err(ns->netdev, "unexpected proto=%d\n", xs->id.proto);
		return false;
	}

	ipsec->tx++;

	return true;
}