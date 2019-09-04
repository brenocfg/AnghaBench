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
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 scalar_t__ TCP_CLOSE ; 
 int __inet_hash (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

int inet6_hash(struct sock *sk)
{
	int err = 0;

	if (sk->sk_state != TCP_CLOSE) {
		local_bh_disable();
		err = __inet_hash(sk, NULL);
		local_bh_enable();
	}

	return err;
}