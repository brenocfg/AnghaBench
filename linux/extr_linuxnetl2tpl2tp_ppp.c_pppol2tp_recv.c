#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; } ;
struct sk_buff {scalar_t__* data; } ;
struct pppox_sock {int /*<<< orphan*/  chan; } ;
struct pppol2tp_session {int /*<<< orphan*/  sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; } ;
struct l2tp_session {int /*<<< orphan*/  name; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2TP_MSG_DATA ; 
 int PPPOX_BOUND ; 
 scalar_t__ PPP_ALLSTATIONS ; 
 scalar_t__ PPP_UI ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2tp_dbg (struct l2tp_session*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l2tp_info (struct l2tp_session*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct pppol2tp_session* l2tp_session_priv (struct l2tp_session*) ; 
 int /*<<< orphan*/  ppp_input (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 
 struct sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void pppol2tp_recv(struct l2tp_session *session, struct sk_buff *skb, int data_len)
{
	struct pppol2tp_session *ps = l2tp_session_priv(session);
	struct sock *sk = NULL;

	/* If the socket is bound, send it in to PPP's input queue. Otherwise
	 * queue it on the session socket.
	 */
	rcu_read_lock();
	sk = rcu_dereference(ps->sk);
	if (sk == NULL)
		goto no_sock;

	/* If the first two bytes are 0xFF03, consider that it is the PPP's
	 * Address and Control fields and skip them. The L2TP module has always
	 * worked this way, although, in theory, the use of these fields should
	 * be negociated and handled at the PPP layer. These fields are
	 * constant: 0xFF is the All-Stations Address and 0x03 the Unnumbered
	 * Information command with Poll/Final bit set to zero (RFC 1662).
	 */
	if (pskb_may_pull(skb, 2) && skb->data[0] == PPP_ALLSTATIONS &&
	    skb->data[1] == PPP_UI)
		skb_pull(skb, 2);

	if (sk->sk_state & PPPOX_BOUND) {
		struct pppox_sock *po;

		l2tp_dbg(session, L2TP_MSG_DATA,
			 "%s: recv %d byte data frame, passing to ppp\n",
			 session->name, data_len);

		po = pppox_sk(sk);
		ppp_input(&po->chan, skb);
	} else {
		l2tp_dbg(session, L2TP_MSG_DATA,
			 "%s: recv %d byte data frame, passing to L2TP socket\n",
			 session->name, data_len);

		if (sock_queue_rcv_skb(sk, skb) < 0) {
			atomic_long_inc(&session->stats.rx_errors);
			kfree_skb(skb);
		}
	}
	rcu_read_unlock();

	return;

no_sock:
	rcu_read_unlock();
	l2tp_info(session, L2TP_MSG_DATA, "%s: no socket\n", session->name);
	kfree_skb(skb);
}