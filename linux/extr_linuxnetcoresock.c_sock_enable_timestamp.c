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
struct sock {unsigned long sk_flags; } ;

/* Variables and functions */
 unsigned long SK_FLAGS_TIMESTAMP ; 
 int /*<<< orphan*/  net_enable_timestamp () ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int) ; 
 scalar_t__ sock_needs_netstamp (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int) ; 

void sock_enable_timestamp(struct sock *sk, int flag)
{
	if (!sock_flag(sk, flag)) {
		unsigned long previous_flags = sk->sk_flags;

		sock_set_flag(sk, flag);
		/*
		 * we just set one of the two flags which require net
		 * time stamping, but time stamping might have been on
		 * already because of the other one
		 */
		if (sock_needs_netstamp(sk) &&
		    !(previous_flags & SK_FLAGS_TIMESTAMP))
			net_enable_timestamp();
	}
}