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
struct sock {int /*<<< orphan*/ * sk_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 

void
netlink_kernel_release(struct sock *sk)
{
	if (sk == NULL || sk->sk_socket == NULL)
		return;

	sock_release(sk->sk_socket);
}