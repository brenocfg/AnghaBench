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
struct xfrm_state {TYPE_4__* repl; TYPE_1__* type; struct xfrm_replay_state_esn* replay_esn; } ;
struct xfrm_replay_state_esn {scalar_t__ oseq; scalar_t__ oseq_hi; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_7__ {scalar_t__ low; scalar_t__ hi; } ;
struct TYPE_8__ {TYPE_2__ output; } ;
struct TYPE_10__ {TYPE_3__ seq; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* notify ) (struct xfrm_state*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  XFRM_REPLAY_UPDATE ; 
 TYPE_5__* XFRM_SKB_CB (struct sk_buff*) ; 
 int XFRM_TYPE_REPLAY_PROT ; 
 int /*<<< orphan*/  stub1 (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xfrm_aevent_is_on (struct net*) ; 
 int /*<<< orphan*/  xfrm_audit_state_replay_overflow (struct xfrm_state*,struct sk_buff*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_replay_overflow_esn(struct xfrm_state *x, struct sk_buff *skb)
{
	int err = 0;
	struct xfrm_replay_state_esn *replay_esn = x->replay_esn;
	struct net *net = xs_net(x);

	if (x->type->flags & XFRM_TYPE_REPLAY_PROT) {
		XFRM_SKB_CB(skb)->seq.output.low = ++replay_esn->oseq;
		XFRM_SKB_CB(skb)->seq.output.hi = replay_esn->oseq_hi;

		if (unlikely(replay_esn->oseq == 0)) {
			XFRM_SKB_CB(skb)->seq.output.hi = ++replay_esn->oseq_hi;

			if (replay_esn->oseq_hi == 0) {
				replay_esn->oseq--;
				replay_esn->oseq_hi--;
				xfrm_audit_state_replay_overflow(x, skb);
				err = -EOVERFLOW;

				return err;
			}
		}
		if (xfrm_aevent_is_on(net))
			x->repl->notify(x, XFRM_REPLAY_UPDATE);
	}

	return err;
}