#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ oseq; } ;
struct xfrm_state {TYPE_4__* repl; TYPE_3__ replay; TYPE_5__* type; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_7__ {scalar_t__ low; scalar_t__ hi; } ;
struct TYPE_8__ {TYPE_1__ output; } ;
struct TYPE_12__ {TYPE_2__ seq; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* notify ) (struct xfrm_state*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  XFRM_REPLAY_UPDATE ; 
 TYPE_6__* XFRM_SKB_CB (struct sk_buff*) ; 
 int XFRM_TYPE_REPLAY_PROT ; 
 int /*<<< orphan*/  stub1 (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xfrm_aevent_is_on (struct net*) ; 
 int /*<<< orphan*/  xfrm_audit_state_replay_overflow (struct xfrm_state*,struct sk_buff*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_replay_overflow(struct xfrm_state *x, struct sk_buff *skb)
{
	int err = 0;
	struct net *net = xs_net(x);

	if (x->type->flags & XFRM_TYPE_REPLAY_PROT) {
		XFRM_SKB_CB(skb)->seq.output.low = ++x->replay.oseq;
		XFRM_SKB_CB(skb)->seq.output.hi = 0;
		if (unlikely(x->replay.oseq == 0)) {
			x->replay.oseq--;
			xfrm_audit_state_replay_overflow(x, skb);
			err = -EOVERFLOW;

			return err;
		}
		if (xfrm_aevent_is_on(net))
			x->repl->notify(x, XFRM_REPLAY_UPDATE);
	}

	return err;
}