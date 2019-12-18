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
 int SK_FLAGS_TIMESTAMP ; 
 int /*<<< orphan*/  net_disable_timestamp () ; 
 scalar_t__ sock_needs_netstamp (struct sock*) ; 

__attribute__((used)) static void sock_disable_timestamp(struct sock *sk, unsigned long flags)
{
	if (sk->sk_flags & flags) {
		sk->sk_flags &= ~flags;
		if (sock_needs_netstamp(sk) &&
		    !(sk->sk_flags & SK_FLAGS_TIMESTAMP))
			net_disable_timestamp();
	}
}