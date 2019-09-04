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
struct pktq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 struct sk_buff* brcmu_pktq_pdeq_tail (struct pktq*,int) ; 
 struct sk_buff* brcmu_pktq_peek_tail (struct pktq*,int*) ; 
 struct sk_buff* brcmu_pktq_penq (struct pktq*,int,struct sk_buff*) ; 
 scalar_t__ pktq_full (struct pktq*) ; 
 scalar_t__ pktq_pfull (struct pktq*,int) ; 

__attribute__((used)) static bool brcmf_sdio_prec_enq(struct pktq *q, struct sk_buff *pkt, int prec)
{
	struct sk_buff *p;
	int eprec = -1;		/* precedence to evict from */

	/* Fast case, precedence queue is not full and we are also not
	 * exceeding total queue length
	 */
	if (!pktq_pfull(q, prec) && !pktq_full(q)) {
		brcmu_pktq_penq(q, prec, pkt);
		return true;
	}

	/* Determine precedence from which to evict packet, if any */
	if (pktq_pfull(q, prec)) {
		eprec = prec;
	} else if (pktq_full(q)) {
		p = brcmu_pktq_peek_tail(q, &eprec);
		if (eprec > prec)
			return false;
	}

	/* Evict if needed */
	if (eprec >= 0) {
		/* Detect queueing to unconfigured precedence */
		if (eprec == prec)
			return false;	/* refuse newer (incoming) packet */
		/* Evict packet according to discard policy */
		p = brcmu_pktq_pdeq_tail(q, eprec);
		if (p == NULL)
			brcmf_err("brcmu_pktq_pdeq_tail() failed\n");
		brcmu_pkt_buf_free_skb(p);
	}

	/* Enqueue */
	p = brcmu_pktq_penq(q, prec, pkt);
	if (p == NULL)
		brcmf_err("brcmu_pktq_penq() failed\n");

	return p != NULL;
}