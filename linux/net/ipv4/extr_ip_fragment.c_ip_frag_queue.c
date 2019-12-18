#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; scalar_t__ ip_summed; unsigned long _skb_refdst; int /*<<< orphan*/  truesize; int /*<<< orphan*/  tstamp; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct TYPE_7__ {int flags; int len; int meat; unsigned int max_size; TYPE_4__* fqdir; int /*<<< orphan*/  stamp; struct sk_buff* fragments_tail; } ;
struct ipq {unsigned int max_df_size; TYPE_2__ q; int /*<<< orphan*/  ecn; int /*<<< orphan*/  iif; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {struct net* net; } ;
struct TYPE_6__ {int frag_off; int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int INET_FRAG_COMPLETE ; 
 int INET_FRAG_FIRST_IN ; 
 int INET_FRAG_LAST_IN ; 
 TYPE_5__* IPCB (struct sk_buff*) ; 
 int IPFRAG_DUP ; 
 int IPSKB_FRAG_COMPLETE ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASMFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_REASM_OVERLAPS ; 
 int /*<<< orphan*/  IP_DF ; 
 int IP_MF ; 
 int IP_OFFSET ; 
 int /*<<< orphan*/  __IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_frag_mem_limit (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_frag_kill (TYPE_2__*) ; 
 int inet_frag_queue_insert (TYPE_2__*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  ip4_frag_ecn (int /*<<< orphan*/ ) ; 
 int ip_frag_reasm (struct ipq*,struct sk_buff*,struct sk_buff*,struct net_device*) ; 
 int ip_frag_reinit (struct ipq*) ; 
 int ip_frag_too_far (struct ipq*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ipq_kill (struct ipq*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 int pskb_trim_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_frag_queue(struct ipq *qp, struct sk_buff *skb)
{
	struct net *net = qp->q.fqdir->net;
	int ihl, end, flags, offset;
	struct sk_buff *prev_tail;
	struct net_device *dev;
	unsigned int fragsize;
	int err = -ENOENT;
	u8 ecn;

	if (qp->q.flags & INET_FRAG_COMPLETE)
		goto err;

	if (!(IPCB(skb)->flags & IPSKB_FRAG_COMPLETE) &&
	    unlikely(ip_frag_too_far(qp)) &&
	    unlikely(err = ip_frag_reinit(qp))) {
		ipq_kill(qp);
		goto err;
	}

	ecn = ip4_frag_ecn(ip_hdr(skb)->tos);
	offset = ntohs(ip_hdr(skb)->frag_off);
	flags = offset & ~IP_OFFSET;
	offset &= IP_OFFSET;
	offset <<= 3;		/* offset is in 8-byte chunks */
	ihl = ip_hdrlen(skb);

	/* Determine the position of this fragment. */
	end = offset + skb->len - skb_network_offset(skb) - ihl;
	err = -EINVAL;

	/* Is this the final fragment? */
	if ((flags & IP_MF) == 0) {
		/* If we already have some bits beyond end
		 * or have different end, the segment is corrupted.
		 */
		if (end < qp->q.len ||
		    ((qp->q.flags & INET_FRAG_LAST_IN) && end != qp->q.len))
			goto discard_qp;
		qp->q.flags |= INET_FRAG_LAST_IN;
		qp->q.len = end;
	} else {
		if (end&7) {
			end &= ~7;
			if (skb->ip_summed != CHECKSUM_UNNECESSARY)
				skb->ip_summed = CHECKSUM_NONE;
		}
		if (end > qp->q.len) {
			/* Some bits beyond end -> corruption. */
			if (qp->q.flags & INET_FRAG_LAST_IN)
				goto discard_qp;
			qp->q.len = end;
		}
	}
	if (end == offset)
		goto discard_qp;

	err = -ENOMEM;
	if (!pskb_pull(skb, skb_network_offset(skb) + ihl))
		goto discard_qp;

	err = pskb_trim_rcsum(skb, end - offset);
	if (err)
		goto discard_qp;

	/* Note : skb->rbnode and skb->dev share the same location. */
	dev = skb->dev;
	/* Makes sure compiler wont do silly aliasing games */
	barrier();

	prev_tail = qp->q.fragments_tail;
	err = inet_frag_queue_insert(&qp->q, skb, offset, end);
	if (err)
		goto insert_error;

	if (dev)
		qp->iif = dev->ifindex;

	qp->q.stamp = skb->tstamp;
	qp->q.meat += skb->len;
	qp->ecn |= ecn;
	add_frag_mem_limit(qp->q.fqdir, skb->truesize);
	if (offset == 0)
		qp->q.flags |= INET_FRAG_FIRST_IN;

	fragsize = skb->len + ihl;

	if (fragsize > qp->q.max_size)
		qp->q.max_size = fragsize;

	if (ip_hdr(skb)->frag_off & htons(IP_DF) &&
	    fragsize > qp->max_df_size)
		qp->max_df_size = fragsize;

	if (qp->q.flags == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    qp->q.meat == qp->q.len) {
		unsigned long orefdst = skb->_skb_refdst;

		skb->_skb_refdst = 0UL;
		err = ip_frag_reasm(qp, skb, prev_tail, dev);
		skb->_skb_refdst = orefdst;
		if (err)
			inet_frag_kill(&qp->q);
		return err;
	}

	skb_dst_drop(skb);
	return -EINPROGRESS;

insert_error:
	if (err == IPFRAG_DUP) {
		kfree_skb(skb);
		return -EINVAL;
	}
	err = -EINVAL;
	__IP_INC_STATS(net, IPSTATS_MIB_REASM_OVERLAPS);
discard_qp:
	inet_frag_kill(&qp->q);
	__IP_INC_STATS(net, IPSTATS_MIB_REASMFAILS);
err:
	kfree_skb(skb);
	return err;
}