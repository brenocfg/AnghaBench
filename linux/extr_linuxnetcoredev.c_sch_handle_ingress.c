#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sk_buff *
sch_handle_ingress(struct sk_buff *skb, struct packet_type **pt_prev, int *ret,
		   struct net_device *orig_dev)
{
#ifdef CONFIG_NET_CLS_ACT
	struct mini_Qdisc *miniq = rcu_dereference_bh(skb->dev->miniq_ingress);
	struct tcf_result cl_res;

	/* If there's at least one ingress present somewhere (so
	 * we get here via enabled static key), remaining devices
	 * that are not configured with an ingress qdisc will bail
	 * out here.
	 */
	if (!miniq)
		return skb;

	if (*pt_prev) {
		*ret = deliver_skb(skb, *pt_prev, orig_dev);
		*pt_prev = NULL;
	}

	qdisc_skb_cb(skb)->pkt_len = skb->len;
	skb->tc_at_ingress = 1;
	mini_qdisc_bstats_cpu_update(miniq, skb);

	switch (tcf_classify(skb, miniq->filter_list, &cl_res, false)) {
	case TC_ACT_OK:
	case TC_ACT_RECLASSIFY:
		skb->tc_index = TC_H_MIN(cl_res.classid);
		break;
	case TC_ACT_SHOT:
		mini_qdisc_qstats_cpu_drop(miniq);
		kfree_skb(skb);
		return NULL;
	case TC_ACT_STOLEN:
	case TC_ACT_QUEUED:
	case TC_ACT_TRAP:
		consume_skb(skb);
		return NULL;
	case TC_ACT_REDIRECT:
		/* skb_mac_header check was done by cls/act_bpf, so
		 * we can safely push the L2 header back before
		 * redirecting to another netdev
		 */
		__skb_push(skb, skb->mac_len);
		skb_do_redirect(skb);
		return NULL;
	case TC_ACT_REINSERT:
		/* this does not scrub the packet, and updates stats on error */
		skb_tc_reinsert(skb, &cl_res);
		return NULL;
	default:
		break;
	}
#endif /* CONFIG_NET_CLS_ACT */
	return skb;
}