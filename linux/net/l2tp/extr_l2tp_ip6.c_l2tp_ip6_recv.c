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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {unsigned char* data; int /*<<< orphan*/  len; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct l2tp_tunnel {int debug; int /*<<< orphan*/  name; } ;
struct l2tp_session {struct l2tp_tunnel* tunnel; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int L2TP_MSG_DATA ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 struct sock* __l2tp_ip6_bind_lookup (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2tp_ip6_lock ; 
 int /*<<< orphan*/  l2tp_recv_common (struct l2tp_session*,struct sk_buff*,unsigned char*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 struct l2tp_session* l2tp_session_get (struct net*,scalar_t__) ; 
 scalar_t__ l2tp_v3_ensure_opt_in_linear (struct l2tp_session*,struct sk_buff*,unsigned char**,unsigned char**) ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int sk_receive_skb (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  xfrm6_policy_check (struct sock*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int l2tp_ip6_recv(struct sk_buff *skb)
{
	struct net *net = dev_net(skb->dev);
	struct sock *sk;
	u32 session_id;
	u32 tunnel_id;
	unsigned char *ptr, *optr;
	struct l2tp_session *session;
	struct l2tp_tunnel *tunnel = NULL;
	struct ipv6hdr *iph;
	int length;

	if (!pskb_may_pull(skb, 4))
		goto discard;

	/* Point to L2TP header */
	optr = ptr = skb->data;
	session_id = ntohl(*((__be32 *) ptr));
	ptr += 4;

	/* RFC3931: L2TP/IP packets have the first 4 bytes containing
	 * the session_id. If it is 0, the packet is a L2TP control
	 * frame and the session_id value can be discarded.
	 */
	if (session_id == 0) {
		__skb_pull(skb, 4);
		goto pass_up;
	}

	/* Ok, this is a data packet. Lookup the session. */
	session = l2tp_session_get(net, session_id);
	if (!session)
		goto discard;

	tunnel = session->tunnel;
	if (!tunnel)
		goto discard_sess;

	/* Trace packet contents, if enabled */
	if (tunnel->debug & L2TP_MSG_DATA) {
		length = min(32u, skb->len);
		if (!pskb_may_pull(skb, length))
			goto discard_sess;

		/* Point to L2TP header */
		optr = ptr = skb->data;
		ptr += 4;
		pr_debug("%s: ip recv\n", tunnel->name);
		print_hex_dump_bytes("", DUMP_PREFIX_OFFSET, ptr, length);
	}

	if (l2tp_v3_ensure_opt_in_linear(session, skb, &ptr, &optr))
		goto discard_sess;

	l2tp_recv_common(session, skb, ptr, optr, 0, skb->len);
	l2tp_session_dec_refcount(session);

	return 0;

pass_up:
	/* Get the tunnel_id from the L2TP header */
	if (!pskb_may_pull(skb, 12))
		goto discard;

	if ((skb->data[0] & 0xc0) != 0xc0)
		goto discard;

	tunnel_id = ntohl(*(__be32 *) &skb->data[4]);
	iph = ipv6_hdr(skb);

	read_lock_bh(&l2tp_ip6_lock);
	sk = __l2tp_ip6_bind_lookup(net, &iph->daddr, &iph->saddr,
				    inet6_iif(skb), tunnel_id);
	if (!sk) {
		read_unlock_bh(&l2tp_ip6_lock);
		goto discard;
	}
	sock_hold(sk);
	read_unlock_bh(&l2tp_ip6_lock);

	if (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
		goto discard_put;

	nf_reset_ct(skb);

	return sk_receive_skb(sk, skb, 1);

discard_sess:
	l2tp_session_dec_refcount(session);
	goto discard;

discard_put:
	sock_put(sk);

discard:
	kfree_skb(skb);
	return 0;
}