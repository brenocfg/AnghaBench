#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct iov_iter {int dummy; } ;
struct afs_net {int /*<<< orphan*/  socket; } ;
struct afs_call {int /*<<< orphan*/  error; int /*<<< orphan*/  state; int /*<<< orphan*/  service_id; int /*<<< orphan*/  rxcall; TYPE_1__* type; struct iov_iter* _iter; struct afs_net* net; } ;
typedef  enum afs_call_state { ____Placeholder_afs_call_state } afs_call_state ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  AFS_CALL_CL_AWAIT_REPLY 130 
 int /*<<< orphan*/  AFS_CALL_CL_PROC_REPLY ; 
#define  AFS_CALL_COMPLETE 129 
#define  AFS_CALL_SV_AWAIT_REQUEST 128 
 int /*<<< orphan*/  AFS_CALL_SV_REPLYING ; 
 int EAGAIN ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int afs_io_error (struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_io_error_extract ; 
 int /*<<< orphan*/  afs_set_call_complete (struct afs_call*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_set_call_state (struct afs_call*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kdebug (char*,int /*<<< orphan*/ ) ; 
 int rxrpc_kernel_recv_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iov_iter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int afs_extract_data(struct afs_call *call, bool want_more)
{
	struct afs_net *net = call->net;
	struct iov_iter *iter = call->_iter;
	enum afs_call_state state;
	u32 remote_abort = 0;
	int ret;

	_enter("{%s,%zu},%d", call->type->name, iov_iter_count(iter), want_more);

	ret = rxrpc_kernel_recv_data(net->socket, call->rxcall, iter,
				     want_more, &remote_abort,
				     &call->service_id);
	if (ret == 0 || ret == -EAGAIN)
		return ret;

	state = READ_ONCE(call->state);
	if (ret == 1) {
		switch (state) {
		case AFS_CALL_CL_AWAIT_REPLY:
			afs_set_call_state(call, state, AFS_CALL_CL_PROC_REPLY);
			break;
		case AFS_CALL_SV_AWAIT_REQUEST:
			afs_set_call_state(call, state, AFS_CALL_SV_REPLYING);
			break;
		case AFS_CALL_COMPLETE:
			kdebug("prem complete %d", call->error);
			return afs_io_error(call, afs_io_error_extract);
		default:
			break;
		}
		return 0;
	}

	afs_set_call_complete(call, ret, remote_abort);
	return ret;
}