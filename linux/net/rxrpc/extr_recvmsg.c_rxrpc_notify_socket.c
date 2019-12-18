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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;
struct rxrpc_sock {int /*<<< orphan*/  recvmsg_lock; int /*<<< orphan*/  recvmsg_q; struct sock sk; } ;
struct rxrpc_call {int /*<<< orphan*/  recvmsg_link; int /*<<< orphan*/  notify_lock; int /*<<< orphan*/  user_call_ID; int /*<<< orphan*/  (* notify_rx ) (struct sock*,struct rxrpc_call*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  socket; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 scalar_t__ RXRPC_CLOSE ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/  (*) (struct sock*)) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct rxrpc_sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rxrpc_call_got ; 
 int /*<<< orphan*/  rxrpc_get_call (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void rxrpc_notify_socket(struct rxrpc_call *call)
{
	struct rxrpc_sock *rx;
	struct sock *sk;

	_enter("%d", call->debug_id);

	if (!list_empty(&call->recvmsg_link))
		return;

	rcu_read_lock();

	rx = rcu_dereference(call->socket);
	sk = &rx->sk;
	if (rx && sk->sk_state < RXRPC_CLOSE) {
		if (call->notify_rx) {
			spin_lock_bh(&call->notify_lock);
			call->notify_rx(sk, call, call->user_call_ID);
			spin_unlock_bh(&call->notify_lock);
		} else {
			write_lock_bh(&rx->recvmsg_lock);
			if (list_empty(&call->recvmsg_link)) {
				rxrpc_get_call(call, rxrpc_call_got);
				list_add_tail(&call->recvmsg_link, &rx->recvmsg_q);
			}
			write_unlock_bh(&rx->recvmsg_lock);

			if (!sock_flag(sk, SOCK_DEAD)) {
				_debug("call %ps", sk->sk_data_ready);
				sk->sk_data_ready(sk);
			}
		}
	}

	rcu_read_unlock();
	_leave("");
}