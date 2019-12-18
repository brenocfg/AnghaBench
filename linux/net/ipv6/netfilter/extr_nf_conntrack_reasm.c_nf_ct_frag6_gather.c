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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  transport_header; TYPE_1__* dev; } ;
struct net {int dummy; } ;
struct ipv6hdr {scalar_t__ payload_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct frag_queue {TYPE_2__ q; } ;
struct frag_hdr {int /*<<< orphan*/  identification; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTO ; 
 scalar_t__ find_prev_fhdr (struct sk_buff*,int /*<<< orphan*/ *,int*,int*) ; 
 struct frag_queue* fq_find (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipv6hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_frag_put (TYPE_2__*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int nf_ct_frag6_queue (struct frag_queue*,struct sk_buff*,struct frag_hdr*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int nf_ct_frag6_gather(struct net *net, struct sk_buff *skb, u32 user)
{
	u16 savethdr = skb->transport_header;
	int fhoff, nhoff, ret;
	struct frag_hdr *fhdr;
	struct frag_queue *fq;
	struct ipv6hdr *hdr;
	u8 prevhdr;

	/* Jumbo payload inhibits frag. header */
	if (ipv6_hdr(skb)->payload_len == 0) {
		pr_debug("payload len = 0\n");
		return 0;
	}

	if (find_prev_fhdr(skb, &prevhdr, &nhoff, &fhoff) < 0)
		return 0;

	if (!pskb_may_pull(skb, fhoff + sizeof(*fhdr)))
		return -ENOMEM;

	skb_set_transport_header(skb, fhoff);
	hdr = ipv6_hdr(skb);
	fhdr = (struct frag_hdr *)skb_transport_header(skb);

	skb_orphan(skb);
	fq = fq_find(net, fhdr->identification, user, hdr,
		     skb->dev ? skb->dev->ifindex : 0);
	if (fq == NULL) {
		pr_debug("Can't find and can't create new queue\n");
		return -ENOMEM;
	}

	spin_lock_bh(&fq->q.lock);

	ret = nf_ct_frag6_queue(fq, skb, fhdr, nhoff);
	if (ret == -EPROTO) {
		skb->transport_header = savethdr;
		ret = 0;
	}

	spin_unlock_bh(&fq->q.lock);
	inet_frag_put(&fq->q);
	return ret;
}