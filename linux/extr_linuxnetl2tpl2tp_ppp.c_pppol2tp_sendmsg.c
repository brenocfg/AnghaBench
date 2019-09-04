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
struct udphdr {int dummy; } ;
struct socket {struct sock* sk; } ;
struct sock {int sk_state; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct msghdr {int dummy; } ;
struct l2tp_tunnel {scalar_t__ encap; } ;
struct l2tp_session {int hdr_len; struct l2tp_tunnel* tunnel; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ L2TP_ENCAPTYPE_UDP ; 
 int NET_SKB_PAD ; 
 int PPPOX_CONNECTED ; 
 int /*<<< orphan*/  PPP_ALLSTATIONS ; 
 int /*<<< orphan*/  PPP_UI ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2tp_xmit_skb (struct l2tp_session*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,size_t) ; 
 struct l2tp_session* pppol2tp_sock_to_session (struct sock*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct sk_buff* sock_wmalloc (struct sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pppol2tp_sendmsg(struct socket *sock, struct msghdr *m,
			    size_t total_len)
{
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	int error;
	struct l2tp_session *session;
	struct l2tp_tunnel *tunnel;
	int uhlen;

	error = -ENOTCONN;
	if (sock_flag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		goto error;

	/* Get session and tunnel contexts */
	error = -EBADF;
	session = pppol2tp_sock_to_session(sk);
	if (session == NULL)
		goto error;

	tunnel = session->tunnel;

	uhlen = (tunnel->encap == L2TP_ENCAPTYPE_UDP) ? sizeof(struct udphdr) : 0;

	/* Allocate a socket buffer */
	error = -ENOMEM;
	skb = sock_wmalloc(sk, NET_SKB_PAD + sizeof(struct iphdr) +
			   uhlen + session->hdr_len +
			   2 + total_len, /* 2 bytes for PPP_ALLSTATIONS & PPP_UI */
			   0, GFP_KERNEL);
	if (!skb)
		goto error_put_sess;

	/* Reserve space for headers. */
	skb_reserve(skb, NET_SKB_PAD);
	skb_reset_network_header(skb);
	skb_reserve(skb, sizeof(struct iphdr));
	skb_reset_transport_header(skb);
	skb_reserve(skb, uhlen);

	/* Add PPP header */
	skb->data[0] = PPP_ALLSTATIONS;
	skb->data[1] = PPP_UI;
	skb_put(skb, 2);

	/* Copy user data into skb */
	error = memcpy_from_msg(skb_put(skb, total_len), m, total_len);
	if (error < 0) {
		kfree_skb(skb);
		goto error_put_sess;
	}

	local_bh_disable();
	l2tp_xmit_skb(session, skb, session->hdr_len);
	local_bh_enable();

	sock_put(sk);

	return total_len;

error_put_sess:
	sock_put(sk);
error:
	return error;
}