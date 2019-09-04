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
struct sock {scalar_t__ sk_err; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_wait_data (struct sock*,long*,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int sock_error (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int sock_intr_errno (long) ; 

__attribute__((used)) static struct sk_buff *kcm_wait_data(struct sock *sk, int flags,
				     long timeo, int *err)
{
	struct sk_buff *skb;

	while (!(skb = skb_peek(&sk->sk_receive_queue))) {
		if (sk->sk_err) {
			*err = sock_error(sk);
			return NULL;
		}

		if (sock_flag(sk, SOCK_DONE))
			return NULL;

		if ((flags & MSG_DONTWAIT) || !timeo) {
			*err = -EAGAIN;
			return NULL;
		}

		sk_wait_data(sk, &timeo, NULL);

		/* Handle signals */
		if (signal_pending(current)) {
			*err = sock_intr_errno(timeo);
			return NULL;
		}
	}

	return skb;
}