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
struct rxrpc_sock {int /*<<< orphan*/  call_lock; int /*<<< orphan*/  to_be_accepted; int /*<<< orphan*/  recvmsg_lock; } ;
struct rxrpc_call {int /*<<< orphan*/  accept_link; int /*<<< orphan*/  recvmsg_link; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int MSG_PEEK ; 
 int /*<<< orphan*/  RXRPC_NEW_CALL ; 
 int /*<<< orphan*/  SOL_RXRPC ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rxrpc_call_got ; 
 int /*<<< orphan*/  rxrpc_get_call (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_recvmsg_to_be_accepted ; 
 int /*<<< orphan*/  trace_rxrpc_recvmsg (struct rxrpc_call*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_recvmsg_new_call(struct rxrpc_sock *rx,
				  struct rxrpc_call *call,
				  struct msghdr *msg, int flags)
{
	int tmp = 0, ret;

	ret = put_cmsg(msg, SOL_RXRPC, RXRPC_NEW_CALL, 0, &tmp);

	if (ret == 0 && !(flags & MSG_PEEK)) {
		_debug("to be accepted");
		write_lock_bh(&rx->recvmsg_lock);
		list_del_init(&call->recvmsg_link);
		write_unlock_bh(&rx->recvmsg_lock);

		rxrpc_get_call(call, rxrpc_call_got);
		write_lock(&rx->call_lock);
		list_add_tail(&call->accept_link, &rx->to_be_accepted);
		write_unlock(&rx->call_lock);
	}

	trace_rxrpc_recvmsg(call, rxrpc_recvmsg_to_be_accepted, 1, 0, 0, ret);
	return ret;
}