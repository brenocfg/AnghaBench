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
typedef  size_t u32 ;
struct afs_vnode {int /*<<< orphan*/  abort_code; void* type; void* expiry; void* version; } ;
struct afs_file_status {int /*<<< orphan*/  abort_code; void* type; void* expiry; void* version; } ;
struct afs_callback {int /*<<< orphan*/  abort_code; void* type; void* expiry; void* version; } ;
struct afs_call {int unmarshall; size_t count2; size_t count; int /*<<< orphan*/  offset; struct afs_vnode** reply; int /*<<< orphan*/  const* buffer; int /*<<< orphan*/  const tmp; } ;
typedef  int /*<<< orphan*/  const __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_decode_status (struct afs_call*,int /*<<< orphan*/  const**,struct afs_vnode*,struct afs_vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int afs_extract_data (struct afs_call*,int /*<<< orphan*/  const*,int,int) ; 
 int afs_protocol_error (struct afs_call*,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xdr_decode_AFSCallBack (struct afs_call*,struct afs_vnode*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  xdr_decode_AFSVolSync (int /*<<< orphan*/  const**,struct afs_vnode*) ; 

__attribute__((used)) static int afs_deliver_fs_inline_bulk_status(struct afs_call *call)
{
	struct afs_file_status *statuses;
	struct afs_callback *callbacks;
	struct afs_vnode *vnode = call->reply[0];
	const __be32 *bp;
	u32 tmp;
	int ret;

	_enter("{%u}", call->unmarshall);

	switch (call->unmarshall) {
	case 0:
		call->offset = 0;
		call->unmarshall++;

		/* Extract the file status count and array in two steps */
	case 1:
		_debug("extract status count");
		ret = afs_extract_data(call, &call->tmp, 4, true);
		if (ret < 0)
			return ret;

		tmp = ntohl(call->tmp);
		_debug("status count: %u/%u", tmp, call->count2);
		if (tmp != call->count2)
			return afs_protocol_error(call, -EBADMSG);

		call->count = 0;
		call->unmarshall++;
	more_counts:
		call->offset = 0;

	case 2:
		_debug("extract status array %u", call->count);
		ret = afs_extract_data(call, call->buffer, 21 * 4, true);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		statuses = call->reply[1];
		if (afs_decode_status(call, &bp, &statuses[call->count],
				      call->count == 0 ? vnode : NULL,
				      NULL, NULL) < 0)
			return afs_protocol_error(call, -EBADMSG);

		call->count++;
		if (call->count < call->count2)
			goto more_counts;

		call->count = 0;
		call->unmarshall++;
		call->offset = 0;

		/* Extract the callback count and array in two steps */
	case 3:
		_debug("extract CB count");
		ret = afs_extract_data(call, &call->tmp, 4, true);
		if (ret < 0)
			return ret;

		tmp = ntohl(call->tmp);
		_debug("CB count: %u", tmp);
		if (tmp != call->count2)
			return afs_protocol_error(call, -EBADMSG);
		call->count = 0;
		call->unmarshall++;
	more_cbs:
		call->offset = 0;

	case 4:
		_debug("extract CB array");
		ret = afs_extract_data(call, call->buffer, 3 * 4, true);
		if (ret < 0)
			return ret;

		_debug("unmarshall CB array");
		bp = call->buffer;
		callbacks = call->reply[2];
		callbacks[call->count].version	= ntohl(bp[0]);
		callbacks[call->count].expiry	= ntohl(bp[1]);
		callbacks[call->count].type	= ntohl(bp[2]);
		statuses = call->reply[1];
		if (call->count == 0 && vnode && statuses[0].abort_code == 0)
			xdr_decode_AFSCallBack(call, vnode, &bp);
		call->count++;
		if (call->count < call->count2)
			goto more_cbs;

		call->offset = 0;
		call->unmarshall++;

	case 5:
		ret = afs_extract_data(call, call->buffer, 6 * 4, false);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		if (call->reply[3])
			xdr_decode_AFSVolSync(&bp, call->reply[3]);

		call->offset = 0;
		call->unmarshall++;

	case 6:
		break;
	}

	_leave(" = 0 [done]");
	return 0;
}