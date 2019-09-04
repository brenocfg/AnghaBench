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
struct sock {struct l2tp_session* sk_user_data; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct l2tp_session {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ L2TP_SESSION_MAGIC ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppol2tp_session_destruct(struct sock *sk)
{
	struct l2tp_session *session = sk->sk_user_data;

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_write_queue);

	if (session) {
		sk->sk_user_data = NULL;
		BUG_ON(session->magic != L2TP_SESSION_MAGIC);
		l2tp_session_dec_refcount(session);
	}
}