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
struct tcf_result {struct tcf_proto* goto_tp; } ;
struct tcf_proto {scalar_t__ protocol; int (* classify ) (struct sk_buff*,struct tcf_proto const*,struct tcf_result*) ;int prio; TYPE_2__* chain; int /*<<< orphan*/  next; } ;
struct tc_skb_ext {int chain; } ;
struct sk_buff {int dummy; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_4__ {TYPE_1__* block; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ALL ; 
 int TC_ACT_EXT_CMP (int,int /*<<< orphan*/ ) ; 
 int TC_ACT_EXT_VAL_MASK ; 
 int /*<<< orphan*/  TC_ACT_GOTO_CHAIN ; 
 int TC_ACT_RECLASSIFY ; 
 int TC_ACT_SHOT ; 
 int TC_ACT_UNSPEC ; 
 int /*<<< orphan*/  TC_SKB_EXT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_notice_ratelimited (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 struct tcf_proto* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 struct tc_skb_ext* skb_ext_add (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,struct tcf_proto const*,struct tcf_result*) ; 
 scalar_t__ tc_skb_protocol (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int tcf_classify(struct sk_buff *skb, const struct tcf_proto *tp,
		 struct tcf_result *res, bool compat_mode)
{
#ifdef CONFIG_NET_CLS_ACT
	const int max_reclassify_loop = 4;
	const struct tcf_proto *orig_tp = tp;
	const struct tcf_proto *first_tp;
	int limit = 0;

reclassify:
#endif
	for (; tp; tp = rcu_dereference_bh(tp->next)) {
		__be16 protocol = tc_skb_protocol(skb);
		int err;

		if (tp->protocol != protocol &&
		    tp->protocol != htons(ETH_P_ALL))
			continue;

		err = tp->classify(skb, tp, res);
#ifdef CONFIG_NET_CLS_ACT
		if (unlikely(err == TC_ACT_RECLASSIFY && !compat_mode)) {
			first_tp = orig_tp;
			goto reset;
		} else if (unlikely(TC_ACT_EXT_CMP(err, TC_ACT_GOTO_CHAIN))) {
			first_tp = res->goto_tp;

#if IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
			{
				struct tc_skb_ext *ext;

				ext = skb_ext_add(skb, TC_SKB_EXT);
				if (WARN_ON_ONCE(!ext))
					return TC_ACT_SHOT;

				ext->chain = err & TC_ACT_EXT_VAL_MASK;
			}
#endif
			goto reset;
		}
#endif
		if (err >= 0)
			return err;
	}

	return TC_ACT_UNSPEC; /* signal: continue lookup */
#ifdef CONFIG_NET_CLS_ACT
reset:
	if (unlikely(limit++ >= max_reclassify_loop)) {
		net_notice_ratelimited("%u: reclassify loop, rule prio %u, protocol %02x\n",
				       tp->chain->block->index,
				       tp->prio & 0xffff,
				       ntohs(tp->protocol));
		return TC_ACT_SHOT;
	}

	tp = first_tp;
	goto reclassify;
#endif
}