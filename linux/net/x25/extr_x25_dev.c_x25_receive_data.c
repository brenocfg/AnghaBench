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
struct x25_neigh {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_rcvbuf; } ;
struct sk_buff {unsigned short* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned short X25_CALL_REQUEST ; 
 unsigned short X25_CLEAR_CONFIRMATION ; 
 int /*<<< orphan*/  X25_STD_MIN_LEN ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned short) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_add_backlog (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  x25_clear_forward_by_lci (unsigned int) ; 
 struct sock* x25_find_socket (unsigned int,struct x25_neigh*) ; 
 scalar_t__ x25_forward_data (unsigned int,struct x25_neigh*,struct sk_buff*) ; 
 int /*<<< orphan*/  x25_link_control (struct sk_buff*,struct x25_neigh*,unsigned short) ; 
 int x25_process_rx_frame (struct sock*,struct sk_buff*) ; 
 int x25_rx_call_request (struct sk_buff*,struct x25_neigh*,unsigned int) ; 

__attribute__((used)) static int x25_receive_data(struct sk_buff *skb, struct x25_neigh *nb)
{
	struct sock *sk;
	unsigned short frametype;
	unsigned int lci;

	if (!pskb_may_pull(skb, X25_STD_MIN_LEN))
		return 0;

	frametype = skb->data[2];
	lci = ((skb->data[0] << 8) & 0xF00) + ((skb->data[1] << 0) & 0x0FF);

	/*
	 *	LCI of zero is always for us, and its always a link control
	 *	frame.
	 */
	if (lci == 0) {
		x25_link_control(skb, nb, frametype);
		return 0;
	}

	/*
	 *	Find an existing socket.
	 */
	if ((sk = x25_find_socket(lci, nb)) != NULL) {
		int queued = 1;

		skb_reset_transport_header(skb);
		bh_lock_sock(sk);
		if (!sock_owned_by_user(sk)) {
			queued = x25_process_rx_frame(sk, skb);
		} else {
			queued = !sk_add_backlog(sk, skb, READ_ONCE(sk->sk_rcvbuf));
		}
		bh_unlock_sock(sk);
		sock_put(sk);
		return queued;
	}

	/*
	 *	Is is a Call Request ? if so process it.
	 */
	if (frametype == X25_CALL_REQUEST)
		return x25_rx_call_request(skb, nb, lci);

	/*
	 * 	Its not a Call Request, nor is it a control frame.
	 *	Can we forward it?
	 */

	if (x25_forward_data(lci, nb, skb)) {
		if (frametype == X25_CLEAR_CONFIRMATION) {
			x25_clear_forward_by_lci(lci);
		}
		kfree_skb(skb);
		return 1;
	}

/*
	x25_transmit_clear_request(nb, lci, 0x0D);
*/

	if (frametype != X25_CLEAR_CONFIRMATION)
		pr_debug("x25_receive_data(): unknown frame type %2x\n",frametype);

	return 0;
}