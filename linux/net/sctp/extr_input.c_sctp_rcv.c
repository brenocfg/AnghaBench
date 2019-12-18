#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sock {scalar_t__ sk_bound_dev_if; } ;
struct sk_buff {scalar_t__ pkt_type; scalar_t__ len; int csum_valid; int /*<<< orphan*/  dev; } ;
struct sctphdr {int dummy; } ;
struct sctp_transport {int dummy; } ;
struct sctp_ep_common {int /*<<< orphan*/  inqueue; struct sock* sk; } ;
struct sctp_endpoint {struct sctp_ep_common base; } ;
struct sctp_chunkhdr {int dummy; } ;
struct sctp_chunk {struct sctp_ep_common* rcvr; struct sctp_transport* transport; int /*<<< orphan*/  sctp_hdr; } ;
struct sctp_association {struct sctp_ep_common base; } ;
struct sctp_af {scalar_t__ (* skb_iif ) (struct sk_buff*) ;int /*<<< orphan*/  (* addr_valid ) (union sctp_addr*,int /*<<< orphan*/ *,struct sk_buff*) ;int /*<<< orphan*/  (* from_skb ) (union sctp_addr*,struct sk_buff*,int) ;} ;
struct TYPE_5__ {struct sock* ctl_sock; } ;
struct net {TYPE_1__ sctp; } ;
struct TYPE_8__ {struct sctp_chunk* chunk; struct sctp_af* af; } ;
struct TYPE_7__ {int /*<<< orphan*/  version; } ;
struct TYPE_6__ {struct sctp_endpoint* ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PACKET_HOST ; 
 TYPE_4__* SCTP_INPUT_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  SCTP_MIB_INSCTPPACKS ; 
 int /*<<< orphan*/  SCTP_MIB_IN_PKT_BACKLOG ; 
 int /*<<< orphan*/  SCTP_MIB_IN_PKT_DISCARDS ; 
 int /*<<< orphan*/  SCTP_MIB_IN_PKT_SOFTIRQ ; 
 int /*<<< orphan*/  SCTP_MIB_OUTOFBLUES ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  __SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct sctp_association* __sctp_rcv_lookup (struct net*,struct sk_buff*,union sctp_addr*,union sctp_addr*,struct sctp_transport**) ; 
 struct sctp_endpoint* __sctp_rcv_lookup_endpoint (struct net*,struct sk_buff*,union sctp_addr*,union sctp_addr*) ; 
 int /*<<< orphan*/  __skb_decr_checksum_unnecessary (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int ipver2af (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ sctp_add_backlog (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_checksum_disable ; 
 int /*<<< orphan*/  sctp_chunk_free (struct sctp_chunk*) ; 
 struct sctp_chunk* sctp_chunkify (struct sk_buff*,struct sctp_association*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_endpoint_hold (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  sctp_endpoint_put (struct sctp_endpoint*) ; 
 struct sctp_af* sctp_get_af_specific (int) ; 
 int /*<<< orphan*/  sctp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_init_addrs (struct sctp_chunk*,union sctp_addr*,union sctp_addr*) ; 
 int /*<<< orphan*/  sctp_inq_push (int /*<<< orphan*/ *,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_newsk_ready (struct sock*) ; 
 scalar_t__ sctp_rcv_checksum (struct net*,struct sk_buff*) ; 
 scalar_t__ sctp_rcv_ootb (struct sk_buff*) ; 
 TYPE_2__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 
 scalar_t__ sk_filter (struct sock*,struct sk_buff*) ; 
 scalar_t__ skb_csum_unnecessary (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_is_gso_sctp (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  stub1 (union sctp_addr*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub2 (union sctp_addr*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub3 (union sctp_addr*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub4 (union sctp_addr*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ stub5 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfrm_policy_check (struct sock*,int /*<<< orphan*/ ,struct sk_buff*,int) ; 

int sctp_rcv(struct sk_buff *skb)
{
	struct sock *sk;
	struct sctp_association *asoc;
	struct sctp_endpoint *ep = NULL;
	struct sctp_ep_common *rcvr;
	struct sctp_transport *transport = NULL;
	struct sctp_chunk *chunk;
	union sctp_addr src;
	union sctp_addr dest;
	int family;
	struct sctp_af *af;
	struct net *net = dev_net(skb->dev);
	bool is_gso = skb_is_gso(skb) && skb_is_gso_sctp(skb);

	if (skb->pkt_type != PACKET_HOST)
		goto discard_it;

	__SCTP_INC_STATS(net, SCTP_MIB_INSCTPPACKS);

	/* If packet is too small to contain a single chunk, let's not
	 * waste time on it anymore.
	 */
	if (skb->len < sizeof(struct sctphdr) + sizeof(struct sctp_chunkhdr) +
		       skb_transport_offset(skb))
		goto discard_it;

	/* If the packet is fragmented and we need to do crc checking,
	 * it's better to just linearize it otherwise crc computing
	 * takes longer.
	 */
	if ((!is_gso && skb_linearize(skb)) ||
	    !pskb_may_pull(skb, sizeof(struct sctphdr)))
		goto discard_it;

	/* Pull up the IP header. */
	__skb_pull(skb, skb_transport_offset(skb));

	skb->csum_valid = 0; /* Previous value not applicable */
	if (skb_csum_unnecessary(skb))
		__skb_decr_checksum_unnecessary(skb);
	else if (!sctp_checksum_disable &&
		 !is_gso &&
		 sctp_rcv_checksum(net, skb) < 0)
		goto discard_it;
	skb->csum_valid = 1;

	__skb_pull(skb, sizeof(struct sctphdr));

	family = ipver2af(ip_hdr(skb)->version);
	af = sctp_get_af_specific(family);
	if (unlikely(!af))
		goto discard_it;
	SCTP_INPUT_CB(skb)->af = af;

	/* Initialize local addresses for lookups. */
	af->from_skb(&src, skb, 1);
	af->from_skb(&dest, skb, 0);

	/* If the packet is to or from a non-unicast address,
	 * silently discard the packet.
	 *
	 * This is not clearly defined in the RFC except in section
	 * 8.4 - OOTB handling.  However, based on the book "Stream Control
	 * Transmission Protocol" 2.1, "It is important to note that the
	 * IP address of an SCTP transport address must be a routable
	 * unicast address.  In other words, IP multicast addresses and
	 * IP broadcast addresses cannot be used in an SCTP transport
	 * address."
	 */
	if (!af->addr_valid(&src, NULL, skb) ||
	    !af->addr_valid(&dest, NULL, skb))
		goto discard_it;

	asoc = __sctp_rcv_lookup(net, skb, &src, &dest, &transport);

	if (!asoc)
		ep = __sctp_rcv_lookup_endpoint(net, skb, &dest, &src);

	/* Retrieve the common input handling substructure. */
	rcvr = asoc ? &asoc->base : &ep->base;
	sk = rcvr->sk;

	/*
	 * If a frame arrives on an interface and the receiving socket is
	 * bound to another interface, via SO_BINDTODEVICE, treat it as OOTB
	 */
	if (sk->sk_bound_dev_if && (sk->sk_bound_dev_if != af->skb_iif(skb))) {
		if (transport) {
			sctp_transport_put(transport);
			asoc = NULL;
			transport = NULL;
		} else {
			sctp_endpoint_put(ep);
			ep = NULL;
		}
		sk = net->sctp.ctl_sock;
		ep = sctp_sk(sk)->ep;
		sctp_endpoint_hold(ep);
		rcvr = &ep->base;
	}

	/*
	 * RFC 2960, 8.4 - Handle "Out of the blue" Packets.
	 * An SCTP packet is called an "out of the blue" (OOTB)
	 * packet if it is correctly formed, i.e., passed the
	 * receiver's checksum check, but the receiver is not
	 * able to identify the association to which this
	 * packet belongs.
	 */
	if (!asoc) {
		if (sctp_rcv_ootb(skb)) {
			__SCTP_INC_STATS(net, SCTP_MIB_OUTOFBLUES);
			goto discard_release;
		}
	}

	if (!xfrm_policy_check(sk, XFRM_POLICY_IN, skb, family))
		goto discard_release;
	nf_reset_ct(skb);

	if (sk_filter(sk, skb))
		goto discard_release;

	/* Create an SCTP packet structure. */
	chunk = sctp_chunkify(skb, asoc, sk, GFP_ATOMIC);
	if (!chunk)
		goto discard_release;
	SCTP_INPUT_CB(skb)->chunk = chunk;

	/* Remember what endpoint is to handle this packet. */
	chunk->rcvr = rcvr;

	/* Remember the SCTP header. */
	chunk->sctp_hdr = sctp_hdr(skb);

	/* Set the source and destination addresses of the incoming chunk.  */
	sctp_init_addrs(chunk, &src, &dest);

	/* Remember where we came from.  */
	chunk->transport = transport;

	/* Acquire access to the sock lock. Note: We are safe from other
	 * bottom halves on this lock, but a user may be in the lock too,
	 * so check if it is busy.
	 */
	bh_lock_sock(sk);

	if (sk != rcvr->sk) {
		/* Our cached sk is different from the rcvr->sk.  This is
		 * because migrate()/accept() may have moved the association
		 * to a new socket and released all the sockets.  So now we
		 * are holding a lock on the old socket while the user may
		 * be doing something with the new socket.  Switch our veiw
		 * of the current sk.
		 */
		bh_unlock_sock(sk);
		sk = rcvr->sk;
		bh_lock_sock(sk);
	}

	if (sock_owned_by_user(sk) || !sctp_newsk_ready(sk)) {
		if (sctp_add_backlog(sk, skb)) {
			bh_unlock_sock(sk);
			sctp_chunk_free(chunk);
			skb = NULL; /* sctp_chunk_free already freed the skb */
			goto discard_release;
		}
		__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_BACKLOG);
	} else {
		__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_SOFTIRQ);
		sctp_inq_push(&chunk->rcvr->inqueue, chunk);
	}

	bh_unlock_sock(sk);

	/* Release the asoc/ep ref we took in the lookup calls. */
	if (transport)
		sctp_transport_put(transport);
	else
		sctp_endpoint_put(ep);

	return 0;

discard_it:
	__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_DISCARDS);
	kfree_skb(skb);
	return 0;

discard_release:
	/* Release the asoc/ep ref we took in the lookup calls. */
	if (transport)
		sctp_transport_put(transport);
	else
		sctp_endpoint_put(ep);

	goto discard_it;
}