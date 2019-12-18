#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_9__ {TYPE_2__ v4; } ;
struct TYPE_10__ {int len; scalar_t__ max_size; TYPE_3__ key; int /*<<< orphan*/ * last_run_head; int /*<<< orphan*/ * fragments_tail; int /*<<< orphan*/  rb_fragments; TYPE_1__* fqdir; } ;
struct ipq {size_t ecn; scalar_t__ max_df_size; TYPE_4__ q; } ;
struct iphdr {int tos; void* frag_off; void* tot_len; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  frag_max_size; } ;
struct TYPE_7__ {struct net* net; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 TYPE_6__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSKB_FRAG_PMTU ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMOKS ; 
 int IP_DF ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  __IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  inet_frag_reasm_finish (TYPE_4__*,struct sk_buff*,void*,int /*<<< orphan*/ ) ; 
 void* inet_frag_reasm_prepare (TYPE_4__*,struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_frag_coalesce_ok (struct ipq*) ; 
 int* ip_frag_ecn_table ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  ipq_kill (struct ipq*) ; 
 int /*<<< orphan*/  max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,struct ipq*) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_frag_reasm(struct ipq *qp, struct sk_buff *skb,
			 struct sk_buff *prev_tail, struct net_device *dev)
{
	struct net *net = qp->q.fqdir->net;
	struct iphdr *iph;
	void *reasm_data;
	int len, err;
	u8 ecn;

	ipq_kill(qp);

	ecn = ip_frag_ecn_table[qp->ecn];
	if (unlikely(ecn == 0xff)) {
		err = -EINVAL;
		goto out_fail;
	}

	/* Make the one we just received the head. */
	reasm_data = inet_frag_reasm_prepare(&qp->q, skb, prev_tail);
	if (!reasm_data)
		goto out_nomem;

	len = ip_hdrlen(skb) + qp->q.len;
	err = -E2BIG;
	if (len > 65535)
		goto out_oversize;

	inet_frag_reasm_finish(&qp->q, skb, reasm_data,
			       ip_frag_coalesce_ok(qp));

	skb->dev = dev;
	IPCB(skb)->frag_max_size = max(qp->max_df_size, qp->q.max_size);

	iph = ip_hdr(skb);
	iph->tot_len = htons(len);
	iph->tos |= ecn;

	/* When we set IP_DF on a refragmented skb we must also force a
	 * call to ip_fragment to avoid forwarding a DF-skb of size s while
	 * original sender only sent fragments of size f (where f < s).
	 *
	 * We only set DF/IPSKB_FRAG_PMTU if such DF fragment was the largest
	 * frag seen to avoid sending tiny DF-fragments in case skb was built
	 * from one very small df-fragment and one large non-df frag.
	 */
	if (qp->max_df_size == qp->q.max_size) {
		IPCB(skb)->flags |= IPSKB_FRAG_PMTU;
		iph->frag_off = htons(IP_DF);
	} else {
		iph->frag_off = 0;
	}

	ip_send_check(iph);

	__IP_INC_STATS(net, IPSTATS_MIB_REASMOKS);
	qp->q.rb_fragments = RB_ROOT;
	qp->q.fragments_tail = NULL;
	qp->q.last_run_head = NULL;
	return 0;

out_nomem:
	net_dbg_ratelimited("queue_glue: no memory for gluing queue %p\n", qp);
	err = -ENOMEM;
	goto out_fail;
out_oversize:
	net_info_ratelimited("Oversized IP packet from %pI4\n", &qp->q.key.v4.saddr);
out_fail:
	__IP_INC_STATS(net, IPSTATS_MIB_REASMFAILS);
	return err;
}