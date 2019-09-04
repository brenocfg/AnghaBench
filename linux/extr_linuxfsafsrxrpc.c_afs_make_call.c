#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_rxrpc {int /*<<< orphan*/  transport; } ;
struct rxrpc_call {int dummy; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iter; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct kvec {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct afs_call {int async; int request_size; scalar_t__ last; scalar_t__ first; int error; int /*<<< orphan*/  abort_code; int /*<<< orphan*/  service_id; TYPE_2__* net; int /*<<< orphan*/  state; scalar_t__ send_pages; int /*<<< orphan*/  request; struct rxrpc_call* rxcall; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  upgrade; int /*<<< orphan*/  key; scalar_t__ last_to; scalar_t__ first_offset; TYPE_1__* type; } ;
struct afs_addr_cursor {int responded; int error; int /*<<< orphan*/  abort_code; struct sockaddr_rxrpc* addr; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  socket; int /*<<< orphan*/  nr_outstanding_calls; } ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_COMPLETE ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ECONNABORTED ; 
 long EINPROGRESS ; 
 scalar_t__ IS_ERR (struct rxrpc_call*) ; 
 int ITER_KVEC ; 
 int MSG_MORE ; 
 int MSG_WAITALL ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct rxrpc_call*) ; 
 int READ ; 
 int /*<<< orphan*/  RX_USER_ABORT ; 
 int WRITE ; 
 int /*<<< orphan*/  _debug (char*,struct afs_call*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  afs_notify_end_request_tx ; 
 int /*<<< orphan*/  afs_put_call (struct afs_call*) ; 
 int afs_send_pages (struct afs_call*,struct msghdr*) ; 
 long afs_wait_for_call_to_complete (struct afs_call*,struct afs_addr_cursor*) ; 
 int /*<<< orphan*/  afs_wake_up_async_call ; 
 int /*<<< orphan*/  afs_wake_up_call_waiter ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int,struct kvec*,int,int) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_abort_call (int /*<<< orphan*/ ,struct rxrpc_call*,int /*<<< orphan*/ ,int,char*) ; 
 struct rxrpc_call* rxrpc_kernel_begin_call (int /*<<< orphan*/ ,struct sockaddr_rxrpc*,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_recv_data (int /*<<< orphan*/ ,struct rxrpc_call*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rxrpc_kernel_send_data (int /*<<< orphan*/ ,struct rxrpc_call*,struct msghdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_call_done (struct afs_call*) ; 

long afs_make_call(struct afs_addr_cursor *ac, struct afs_call *call,
		   gfp_t gfp, bool async)
{
	struct sockaddr_rxrpc *srx = ac->addr;
	struct rxrpc_call *rxcall;
	struct msghdr msg;
	struct kvec iov[1];
	s64 tx_total_len;
	int ret;

	_enter(",{%pISp},", &srx->transport);

	ASSERT(call->type != NULL);
	ASSERT(call->type->name != NULL);

	_debug("____MAKE %p{%s,%x} [%d]____",
	       call, call->type->name, key_serial(call->key),
	       atomic_read(&call->net->nr_outstanding_calls));

	call->async = async;

	/* Work out the length we're going to transmit.  This is awkward for
	 * calls such as FS.StoreData where there's an extra injection of data
	 * after the initial fixed part.
	 */
	tx_total_len = call->request_size;
	if (call->send_pages) {
		if (call->last == call->first) {
			tx_total_len += call->last_to - call->first_offset;
		} else {
			/* It looks mathematically like you should be able to
			 * combine the following lines with the ones above, but
			 * unsigned arithmetic is fun when it wraps...
			 */
			tx_total_len += PAGE_SIZE - call->first_offset;
			tx_total_len += call->last_to;
			tx_total_len += (call->last - call->first - 1) * PAGE_SIZE;
		}
	}

	/* create a call */
	rxcall = rxrpc_kernel_begin_call(call->net->socket, srx, call->key,
					 (unsigned long)call,
					 tx_total_len, gfp,
					 (async ?
					  afs_wake_up_async_call :
					  afs_wake_up_call_waiter),
					 call->upgrade,
					 call->debug_id);
	if (IS_ERR(rxcall)) {
		ret = PTR_ERR(rxcall);
		goto error_kill_call;
	}

	call->rxcall = rxcall;

	/* send the request */
	iov[0].iov_base	= call->request;
	iov[0].iov_len	= call->request_size;

	msg.msg_name		= NULL;
	msg.msg_namelen		= 0;
	iov_iter_kvec(&msg.msg_iter, WRITE | ITER_KVEC, iov, 1,
		      call->request_size);
	msg.msg_control		= NULL;
	msg.msg_controllen	= 0;
	msg.msg_flags		= MSG_WAITALL | (call->send_pages ? MSG_MORE : 0);

	ret = rxrpc_kernel_send_data(call->net->socket, rxcall,
				     &msg, call->request_size,
				     afs_notify_end_request_tx);
	if (ret < 0)
		goto error_do_abort;

	if (call->send_pages) {
		ret = afs_send_pages(call, &msg);
		if (ret < 0)
			goto error_do_abort;
	}

	/* at this point, an async call may no longer exist as it may have
	 * already completed */
	if (call->async)
		return -EINPROGRESS;

	return afs_wait_for_call_to_complete(call, ac);

error_do_abort:
	call->state = AFS_CALL_COMPLETE;
	if (ret != -ECONNABORTED) {
		rxrpc_kernel_abort_call(call->net->socket, rxcall,
					RX_USER_ABORT, ret, "KSD");
	} else {
		iov_iter_kvec(&msg.msg_iter, READ | ITER_KVEC, NULL, 0, 0);
		rxrpc_kernel_recv_data(call->net->socket, rxcall,
				       &msg.msg_iter, false,
				       &call->abort_code, &call->service_id);
		ac->abort_code = call->abort_code;
		ac->responded = true;
	}
	call->error = ret;
	trace_afs_call_done(call);
error_kill_call:
	afs_put_call(call);
	ac->error = ret;
	_leave(" = %d", ret);
	return ret;
}