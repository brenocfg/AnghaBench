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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_refcnt; } ;

/* Variables and functions */
 scalar_t__ TCP_NEW_SYN_RECV ; 
 scalar_t__ TCP_TIME_WAIT ; 
 int /*<<< orphan*/  inet_reqsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reqsk_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 

void sock_gen_put(struct sock *sk)
{
	if (!refcount_dec_and_test(&sk->sk_refcnt))
		return;

	if (sk->sk_state == TCP_TIME_WAIT)
		inet_twsk_free(inet_twsk(sk));
	else if (sk->sk_state == TCP_NEW_SYN_RECV)
		reqsk_free(inet_reqsk(sk));
	else
		sk_free(sk);
}