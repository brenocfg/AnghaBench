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
struct afs_call {TYPE_1__* type; int /*<<< orphan*/  tmp; int /*<<< orphan*/  operation_ID; int /*<<< orphan*/  _iter; } ;
struct TYPE_2__ {int (* deliver ) (struct afs_call*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_SV_AWAIT_OP_ID ; 
 int /*<<< orphan*/  AFS_CALL_SV_AWAIT_REQUEST ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_cm_incoming_call (struct afs_call*) ; 
 int afs_extract_data (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_set_call_state (struct afs_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int stub1 (struct afs_call*) ; 
 int /*<<< orphan*/  trace_afs_cb_call (struct afs_call*) ; 

__attribute__((used)) static int afs_deliver_cm_op_id(struct afs_call *call)
{
	int ret;

	_enter("{%zu}", iov_iter_count(call->_iter));

	/* the operation ID forms the first four bytes of the request data */
	ret = afs_extract_data(call, true);
	if (ret < 0)
		return ret;

	call->operation_ID = ntohl(call->tmp);
	afs_set_call_state(call, AFS_CALL_SV_AWAIT_OP_ID, AFS_CALL_SV_AWAIT_REQUEST);

	/* ask the cache manager to route the call (it'll change the call type
	 * if successful) */
	if (!afs_cm_incoming_call(call))
		return -ENOTSUPP;

	trace_afs_cb_call(call);

	/* pass responsibility for the remainer of this message off to the
	 * cache manager op */
	return call->type->deliver(call);
}