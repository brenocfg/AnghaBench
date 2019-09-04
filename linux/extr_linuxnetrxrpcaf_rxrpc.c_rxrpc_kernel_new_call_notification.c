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
struct socket {int /*<<< orphan*/  sk; } ;
struct rxrpc_sock {int /*<<< orphan*/  discard_new_call; int /*<<< orphan*/  notify_new_call; } ;
typedef  int /*<<< orphan*/  rxrpc_notify_new_call_t ;
typedef  int /*<<< orphan*/  rxrpc_discard_new_call_t ;

/* Variables and functions */
 struct rxrpc_sock* rxrpc_sk (int /*<<< orphan*/ ) ; 

void rxrpc_kernel_new_call_notification(
	struct socket *sock,
	rxrpc_notify_new_call_t notify_new_call,
	rxrpc_discard_new_call_t discard_new_call)
{
	struct rxrpc_sock *rx = rxrpc_sk(sock->sk);

	rx->notify_new_call = notify_new_call;
	rx->discard_new_call = discard_new_call;
}