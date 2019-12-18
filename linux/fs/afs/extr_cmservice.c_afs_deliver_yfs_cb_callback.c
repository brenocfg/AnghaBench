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
struct TYPE_4__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct yfs_xdr_YFSFid {TYPE_2__ vnode; int /*<<< orphan*/  volume; } ;
struct TYPE_3__ {void* unique; void* vnode_hi; void* vnode; void* vid; } ;
struct afs_callback_break {TYPE_1__ fid; } ;
struct afs_call {int unmarshall; int count; struct yfs_xdr_YFSFid* buffer; struct afs_callback_break* request; int /*<<< orphan*/  tmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_SV_REPLYING ; 
 int /*<<< orphan*/  EBADMSG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int YFSCBMAX ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  afs_check_call_state (struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_eproto_cb_fid_count ; 
 int afs_extract_data (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_to_buf (struct afs_call*,size_t) ; 
 int /*<<< orphan*/  afs_extract_to_tmp (struct afs_call*) ; 
 int afs_find_cm_server_by_peer (struct afs_call*) ; 
 int afs_io_error (struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_io_error_cm_reply ; 
 int afs_protocol_error (struct afs_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t array_size (int,int) ; 
 struct afs_callback_break* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct yfs_xdr_YFSFid* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* xdr_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_deliver_yfs_cb_callback(struct afs_call *call)
{
	struct afs_callback_break *cb;
	struct yfs_xdr_YFSFid *bp;
	size_t size;
	int ret, loop;

	_enter("{%u}", call->unmarshall);

	switch (call->unmarshall) {
	case 0:
		afs_extract_to_tmp(call);
		call->unmarshall++;

		/* extract the FID array and its count in two steps */
		/* Fall through */
	case 1:
		_debug("extract FID count");
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		call->count = ntohl(call->tmp);
		_debug("FID count: %u", call->count);
		if (call->count > YFSCBMAX)
			return afs_protocol_error(call, -EBADMSG,
						  afs_eproto_cb_fid_count);

		size = array_size(call->count, sizeof(struct yfs_xdr_YFSFid));
		call->buffer = kmalloc(size, GFP_KERNEL);
		if (!call->buffer)
			return -ENOMEM;
		afs_extract_to_buf(call, size);
		call->unmarshall++;

		/* Fall through */
	case 2:
		_debug("extract FID array");
		ret = afs_extract_data(call, false);
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
			cb->fid.vid	= xdr_to_u64(bp->volume);
			cb->fid.vnode	= xdr_to_u64(bp->vnode.lo);
			cb->fid.vnode_hi = ntohl(bp->vnode.hi);
			cb->fid.unique	= ntohl(bp->vnode.unique);
			bp++;
		}

		afs_extract_to_tmp(call);
		call->unmarshall++;

	case 3:
		break;
	}

	if (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		return afs_io_error(call, afs_io_error_cm_reply);

	/* We'll need the file server record as that tells us which set of
	 * vnodes to operate upon.
	 */
	return afs_find_cm_server_by_peer(call);
}