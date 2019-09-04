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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __x25_destroy_socket (struct sock*) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void x25_destroy_socket_from_timer(struct sock *sk)
{
	sock_hold(sk);
	bh_lock_sock(sk);
	__x25_destroy_socket(sk);
	bh_unlock_sock(sk);
	sock_put(sk);
}