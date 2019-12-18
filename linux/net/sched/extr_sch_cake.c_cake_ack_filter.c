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
typedef  int /*<<< orphan*/  u32 ;
struct tcphdr {scalar_t__ source; scalar_t__ dest; int /*<<< orphan*/  ack_seq; } ;
typedef  struct sk_buff {struct sk_buff const* next; } const sk_buff ;
struct ipv6hdr {int /*<<< orphan*/  payload_len; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct iphdr {int version; scalar_t__ saddr; scalar_t__ daddr; int ihl; int /*<<< orphan*/  tot_len; } ;
struct cake_sched_data {scalar_t__ ack_filter; } ;
struct cake_flow {struct sk_buff const* head; struct sk_buff const* tail; } ;
typedef  int /*<<< orphan*/  _tcph_check ;
typedef  int /*<<< orphan*/  _tcph ;
typedef  int __be32 ;

/* Variables and functions */
 scalar_t__ CAKE_ACK_AGGRESSIVE ; 
 int TCP_FLAG_ACK ; 
 int TCP_FLAG_CWR ; 
 int TCP_FLAG_ECE ; 
 int TCP_FLAG_SYN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __tcp_hdrlen (struct tcphdr const*) ; 
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 struct iphdr* cake_get_iphdr (struct sk_buff const*,struct ipv6hdr*) ; 
 struct tcphdr* cake_get_tcphdr (struct sk_buff const*,...) ; 
 int /*<<< orphan*/  cake_tcph_get_tstamp (struct tcphdr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cake_tcph_may_drop (struct tcphdr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cake_tcph_sack_compare (struct tcphdr const*,struct tcphdr const*) ; 
 scalar_t__ ipv6_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff const*) ; 
 int tcp_flag_word (struct tcphdr const*) ; 

__attribute__((used)) static struct sk_buff *cake_ack_filter(struct cake_sched_data *q,
				       struct cake_flow *flow)
{
	bool aggressive = q->ack_filter == CAKE_ACK_AGGRESSIVE;
	struct sk_buff *elig_ack = NULL, *elig_ack_prev = NULL;
	struct sk_buff *skb_check, *skb_prev = NULL;
	const struct ipv6hdr *ipv6h, *ipv6h_check;
	unsigned char _tcph[64], _tcph_check[64];
	const struct tcphdr *tcph, *tcph_check;
	const struct iphdr *iph, *iph_check;
	struct ipv6hdr _iph, _iph_check;
	const struct sk_buff *skb;
	int seglen, num_found = 0;
	u32 tstamp = 0, tsecr = 0;
	__be32 elig_flags = 0;
	int sack_comp;

	/* no other possible ACKs to filter */
	if (flow->head == flow->tail)
		return NULL;

	skb = flow->tail;
	tcph = cake_get_tcphdr(skb, _tcph, sizeof(_tcph));
	iph = cake_get_iphdr(skb, &_iph);
	if (!tcph)
		return NULL;

	cake_tcph_get_tstamp(tcph, &tstamp, &tsecr);

	/* the 'triggering' packet need only have the ACK flag set.
	 * also check that SYN is not set, as there won't be any previous ACKs.
	 */
	if ((tcp_flag_word(tcph) &
	     (TCP_FLAG_ACK | TCP_FLAG_SYN)) != TCP_FLAG_ACK)
		return NULL;

	/* the 'triggering' ACK is at the tail of the queue, we have already
	 * returned if it is the only packet in the flow. loop through the rest
	 * of the queue looking for pure ACKs with the same 5-tuple as the
	 * triggering one.
	 */
	for (skb_check = flow->head;
	     skb_check && skb_check != skb;
	     skb_prev = skb_check, skb_check = skb_check->next) {
		iph_check = cake_get_iphdr(skb_check, &_iph_check);
		tcph_check = cake_get_tcphdr(skb_check, &_tcph_check,
					     sizeof(_tcph_check));

		/* only TCP packets with matching 5-tuple are eligible, and only
		 * drop safe headers
		 */
		if (!tcph_check || iph->version != iph_check->version ||
		    tcph_check->source != tcph->source ||
		    tcph_check->dest != tcph->dest)
			continue;

		if (iph_check->version == 4) {
			if (iph_check->saddr != iph->saddr ||
			    iph_check->daddr != iph->daddr)
				continue;

			seglen = ntohs(iph_check->tot_len) -
				       (4 * iph_check->ihl);
		} else if (iph_check->version == 6) {
			ipv6h = (struct ipv6hdr *)iph;
			ipv6h_check = (struct ipv6hdr *)iph_check;

			if (ipv6_addr_cmp(&ipv6h_check->saddr, &ipv6h->saddr) ||
			    ipv6_addr_cmp(&ipv6h_check->daddr, &ipv6h->daddr))
				continue;

			seglen = ntohs(ipv6h_check->payload_len);
		} else {
			WARN_ON(1);  /* shouldn't happen */
			continue;
		}

		/* If the ECE/CWR flags changed from the previous eligible
		 * packet in the same flow, we should no longer be dropping that
		 * previous packet as this would lose information.
		 */
		if (elig_ack && (tcp_flag_word(tcph_check) &
				 (TCP_FLAG_ECE | TCP_FLAG_CWR)) != elig_flags) {
			elig_ack = NULL;
			elig_ack_prev = NULL;
			num_found--;
		}

		/* Check TCP options and flags, don't drop ACKs with segment
		 * data, and don't drop ACKs with a higher cumulative ACK
		 * counter than the triggering packet. Check ACK seqno here to
		 * avoid parsing SACK options of packets we are going to exclude
		 * anyway.
		 */
		if (!cake_tcph_may_drop(tcph_check, tstamp, tsecr) ||
		    (seglen - __tcp_hdrlen(tcph_check)) != 0 ||
		    after(ntohl(tcph_check->ack_seq), ntohl(tcph->ack_seq)))
			continue;

		/* Check SACK options. The triggering packet must SACK more data
		 * than the ACK under consideration, or SACK the same range but
		 * have a larger cumulative ACK counter. The latter is a
		 * pathological case, but is contained in the following check
		 * anyway, just to be safe.
		 */
		sack_comp = cake_tcph_sack_compare(tcph_check, tcph);

		if (sack_comp < 0 ||
		    (ntohl(tcph_check->ack_seq) == ntohl(tcph->ack_seq) &&
		     sack_comp == 0))
			continue;

		/* At this point we have found an eligible pure ACK to drop; if
		 * we are in aggressive mode, we are done. Otherwise, keep
		 * searching unless this is the second eligible ACK we
		 * found.
		 *
		 * Since we want to drop ACK closest to the head of the queue,
		 * save the first eligible ACK we find, even if we need to loop
		 * again.
		 */
		if (!elig_ack) {
			elig_ack = skb_check;
			elig_ack_prev = skb_prev;
			elig_flags = (tcp_flag_word(tcph_check)
				      & (TCP_FLAG_ECE | TCP_FLAG_CWR));
		}

		if (num_found++ > 0)
			goto found;
	}

	/* We made it through the queue without finding two eligible ACKs . If
	 * we found a single eligible ACK we can drop it in aggressive mode if
	 * we can guarantee that this does not interfere with ECN flag
	 * information. We ensure this by dropping it only if the enqueued
	 * packet is consecutive with the eligible ACK, and their flags match.
	 */
	if (elig_ack && aggressive && elig_ack->next == skb &&
	    (elig_flags == (tcp_flag_word(tcph) &
			    (TCP_FLAG_ECE | TCP_FLAG_CWR))))
		goto found;

	return NULL;

found:
	if (elig_ack_prev)
		elig_ack_prev->next = elig_ack->next;
	else
		flow->head = elig_ack->next;

	skb_mark_not_on_list(elig_ack);

	return elig_ack;
}