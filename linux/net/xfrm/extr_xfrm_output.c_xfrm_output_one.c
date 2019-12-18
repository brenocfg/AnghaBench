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
struct TYPE_10__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct TYPE_8__ {scalar_t__ state; } ;
struct TYPE_7__ {int flags; } ;
struct xfrm_state {int /*<<< orphan*/  lock; TYPE_6__* type; TYPE_5__* type_offload; TYPE_4__ curlft; TYPE_3__* repl; TYPE_2__ km; TYPE_1__ outer_mode; } ;
struct sk_buff {scalar_t__ encapsulation; scalar_t__ len; int /*<<< orphan*/  mark; } ;
struct net {int dummy; } ;
struct dst_entry {struct xfrm_state* xfrm; } ;
struct TYPE_12__ {int (* output ) (struct xfrm_state*,struct sk_buff*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* encap ) (struct xfrm_state*,struct sk_buff*) ;} ;
struct TYPE_9__ {int (* overflow ) (struct xfrm_state*,struct sk_buff*) ;} ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEEXPIRED ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEINVALID ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEMODEERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATEPROTOERROR ; 
 int /*<<< orphan*/  LINUX_MIB_XFRMOUTSTATESEQERROR ; 
 int /*<<< orphan*/  XFRM_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int XFRM_MODE_FLAG_TUNNEL ; 
 scalar_t__ XFRM_STATE_VALID ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_force (struct sk_buff*) ; 
 struct dst_entry* skb_dst_pop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct xfrm_state*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct xfrm_state*,struct sk_buff*) ; 
 int stub3 (struct xfrm_state*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xfrm_offload (struct sk_buff*) ; 
 int xfrm_outer_mode_output (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm_skb_check_space (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_smark_get (int /*<<< orphan*/ ,struct xfrm_state*) ; 
 int xfrm_state_check_expire (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm_output_one(struct sk_buff *skb, int err)
{
	struct dst_entry *dst = skb_dst(skb);
	struct xfrm_state *x = dst->xfrm;
	struct net *net = xs_net(x);

	if (err <= 0)
		goto resume;

	do {
		err = xfrm_skb_check_space(skb);
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			goto error_nolock;
		}

		skb->mark = xfrm_smark_get(skb->mark, x);

		err = xfrm_outer_mode_output(x, skb);
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEMODEERROR);
			goto error_nolock;
		}

		spin_lock_bh(&x->lock);

		if (unlikely(x->km.state != XFRM_STATE_VALID)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEINVALID);
			err = -EINVAL;
			goto error;
		}

		err = xfrm_state_check_expire(x);
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEEXPIRED);
			goto error;
		}

		err = x->repl->overflow(x, skb);
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATESEQERROR);
			goto error;
		}

		x->curlft.bytes += skb->len;
		x->curlft.packets++;

		spin_unlock_bh(&x->lock);

		skb_dst_force(skb);
		if (!skb_dst(skb)) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			err = -EHOSTUNREACH;
			goto error_nolock;
		}

		if (xfrm_offload(skb)) {
			x->type_offload->encap(x, skb);
		} else {
			/* Inner headers are invalid now. */
			skb->encapsulation = 0;

			err = x->type->output(x, skb);
			if (err == -EINPROGRESS)
				goto out;
		}

resume:
		if (err) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEPROTOERROR);
			goto error_nolock;
		}

		dst = skb_dst_pop(skb);
		if (!dst) {
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			err = -EHOSTUNREACH;
			goto error_nolock;
		}
		skb_dst_set(skb, dst);
		x = dst->xfrm;
	} while (x && !(x->outer_mode.flags & XFRM_MODE_FLAG_TUNNEL));

	return 0;

error:
	spin_unlock_bh(&x->lock);
error_nolock:
	kfree_skb(skb);
out:
	return err;
}