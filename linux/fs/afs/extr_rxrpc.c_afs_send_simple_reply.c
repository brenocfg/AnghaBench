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
struct msghdr {scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; int /*<<< orphan*/  msg_iter; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct kvec {size_t iov_len; void* iov_base; } ;
struct afs_net {int /*<<< orphan*/  socket; } ;
struct afs_call {int /*<<< orphan*/  rxcall; struct afs_net* net; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RX_USER_ABORT ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_notify_end_reply_tx ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,size_t) ; 
 int /*<<< orphan*/  rxrpc_kernel_abort_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int rxrpc_kernel_send_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msghdr*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_set_tx_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void afs_send_simple_reply(struct afs_call *call, const void *buf, size_t len)
{
	struct afs_net *net = call->net;
	struct msghdr msg;
	struct kvec iov[1];
	int n;

	_enter("");

	rxrpc_kernel_set_tx_length(net->socket, call->rxcall, len);

	iov[0].iov_base		= (void *) buf;
	iov[0].iov_len		= len;
	msg.msg_name		= NULL;
	msg.msg_namelen		= 0;
	iov_iter_kvec(&msg.msg_iter, WRITE, iov, 1, len);
	msg.msg_control		= NULL;
	msg.msg_controllen	= 0;
	msg.msg_flags		= 0;

	n = rxrpc_kernel_send_data(net->socket, call->rxcall, &msg, len,
				   afs_notify_end_reply_tx);
	if (n >= 0) {
		/* Success */
		_leave(" [replied]");
		return;
	}

	if (n == -ENOMEM) {
		_debug("oom");
		rxrpc_kernel_abort_call(net->socket, call->rxcall,
					RX_USER_ABORT, -ENOMEM, "KOO");
	}
	_leave(" [error]");
}