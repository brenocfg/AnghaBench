#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_rxrpc {int dummy; } ;
struct TYPE_5__ {void* type; void* expiry; void* version; } ;
struct TYPE_4__ {void* unique; void* vnode; void* vid; } ;
struct afs_callback_break {TYPE_2__ cb; TYPE_1__ fid; } ;
struct afs_call {int unmarshall; int count; int count2; int /*<<< orphan*/  cm_server; TYPE_3__* net; int /*<<< orphan*/  rxcall; int /*<<< orphan*/  offset; int /*<<< orphan*/ * buffer; struct afs_callback_break* request; int /*<<< orphan*/  tmp; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int AFSCBMAX ; 
 void* AFSCM_CB_UNTYPED ; 
 int /*<<< orphan*/  AFS_CALL_SV_REPLYING ; 
 int /*<<< orphan*/  EBADMSG ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  afs_check_call_state (struct afs_call*,int /*<<< orphan*/ ) ; 
 int afs_extract_data (struct afs_call*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_find_server (TYPE_3__*,struct sockaddr_rxrpc*) ; 
 int afs_protocol_error (struct afs_call*,int /*<<< orphan*/ ) ; 
 int afs_queue_call_work (struct afs_call*) ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 struct afs_callback_break* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_get_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_rxrpc*) ; 
 int /*<<< orphan*/  trace_afs_cm_no_server (struct afs_call*,struct sockaddr_rxrpc*) ; 

__attribute__((used)) static int afs_deliver_cb_callback(struct afs_call *call)
{
	struct afs_callback_break *cb;
	struct sockaddr_rxrpc srx;
	__be32 *bp;
	int ret, loop;

	_enter("{%u}", call->unmarshall);

	switch (call->unmarshall) {
	case 0:
		call->offset = 0;
		call->unmarshall++;

		/* extract the FID array and its count in two steps */
	case 1:
		_debug("extract FID count");
		ret = afs_extract_data(call, &call->tmp, 4, true);
		if (ret < 0)
			return ret;

		call->count = ntohl(call->tmp);
		_debug("FID count: %u", call->count);
		if (call->count > AFSCBMAX)
			return afs_protocol_error(call, -EBADMSG);

		call->buffer = kmalloc(array3_size(call->count, 3, 4),
				       GFP_KERNEL);
		if (!call->buffer)
			return -ENOMEM;
		call->offset = 0;
		call->unmarshall++;

	case 2:
		_debug("extract FID array");
		ret = afs_extract_data(call, call->buffer,
				       call->count * 3 * 4, true);
		if (ret < 0)
			return ret;

		_debug("unmarshall FID array");
		call->request = kcalloc(call->count,
					sizeof(struct afs_callback_break),
					GFP_KERNEL);
		if (!call->request)
			return -ENOMEM;

		cb = call->request;
		bp = call->buffer;
		for (loop = call->count; loop > 0; loop--, cb++) {
			cb->fid.vid	= ntohl(*bp++);
			cb->fid.vnode	= ntohl(*bp++);
			cb->fid.unique	= ntohl(*bp++);
			cb->cb.type	= AFSCM_CB_UNTYPED;
		}

		call->offset = 0;
		call->unmarshall++;

		/* extract the callback array and its count in two steps */
	case 3:
		_debug("extract CB count");
		ret = afs_extract_data(call, &call->tmp, 4, true);
		if (ret < 0)
			return ret;

		call->count2 = ntohl(call->tmp);
		_debug("CB count: %u", call->count2);
		if (call->count2 != call->count && call->count2 != 0)
			return afs_protocol_error(call, -EBADMSG);
		call->offset = 0;
		call->unmarshall++;

	case 4:
		_debug("extract CB array");
		ret = afs_extract_data(call, call->buffer,
				       call->count2 * 3 * 4, false);
		if (ret < 0)
			return ret;

		_debug("unmarshall CB array");
		cb = call->request;
		bp = call->buffer;
		for (loop = call->count2; loop > 0; loop--, cb++) {
			cb->cb.version	= ntohl(*bp++);
			cb->cb.expiry	= ntohl(*bp++);
			cb->cb.type	= ntohl(*bp++);
		}

		call->offset = 0;
		call->unmarshall++;
	case 5:
		break;
	}

	if (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		return -EIO;

	/* we'll need the file server record as that tells us which set of
	 * vnodes to operate upon */
	rxrpc_kernel_get_peer(call->net->socket, call->rxcall, &srx);
	call->cm_server = afs_find_server(call->net, &srx);
	if (!call->cm_server)
		trace_afs_cm_no_server(call, &srx);

	return afs_queue_call_work(call);
}