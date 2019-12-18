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
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_writeable (struct sock*) ; 
 int /*<<< orphan*/  xs_write_space (struct sock*) ; 

__attribute__((used)) static void xs_udp_write_space(struct sock *sk)
{
	read_lock_bh(&sk->sk_callback_lock);

	/* from net/core/sock.c:sock_def_write_space */
	if (sock_writeable(sk))
		xs_write_space(sk);

	read_unlock_bh(&sk->sk_callback_lock);
}