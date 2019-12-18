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
struct yfs_xdr_YFSVolSync {int dummy; } ;
struct yfs_xdr_YFSFetchStatus {int dummy; } ;
struct yfs_xdr_YFSCallBack {int dummy; } ;
struct afs_status_cb {int dummy; } ;
struct afs_call {int unmarshall; size_t count2; size_t count; int /*<<< orphan*/  out_volsync; int /*<<< orphan*/ * buffer; struct afs_status_cb* out_scb; int /*<<< orphan*/  tmp; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_eproto_ibulkst_cb_count ; 
 int /*<<< orphan*/  afs_eproto_ibulkst_count ; 
 int afs_extract_data (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_to_buf (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_to_tmp (struct afs_call*) ; 
 int afs_protocol_error (struct afs_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_decode_YFSCallBack (int /*<<< orphan*/  const**,struct afs_call*,struct afs_status_cb*) ; 
 int xdr_decode_YFSFetchStatus (int /*<<< orphan*/  const**,struct afs_call*,struct afs_status_cb*) ; 
 int /*<<< orphan*/  xdr_decode_YFSVolSync (int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int yfs_deliver_fs_inline_bulk_status(struct afs_call *call)
{
	struct afs_status_cb *scb;
	const __be32 *bp;
	u32 tmp;
	int ret;

	_enter("{%u}", call->unmarshall);

	switch (call->unmarshall) {
	case 0:
		afs_extract_to_tmp(call);
		call->unmarshall++;
		/* Fall through */

		/* Extract the file status count and array in two steps */
	case 1:
		_debug("extract status count");
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		tmp = ntohl(call->tmp);
		_debug("status count: %u/%u", tmp, call->count2);
		if (tmp != call->count2)
			return afs_protocol_error(call, -EBADMSG,
						  afs_eproto_ibulkst_count);

		call->count = 0;
		call->unmarshall++;
	more_counts:
		afs_extract_to_buf(call, sizeof(struct yfs_xdr_YFSFetchStatus));
		/* Fall through */

	case 2:
		_debug("extract status array %u", call->count);
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		scb = &call->out_scb[call->count];
		ret = xdr_decode_YFSFetchStatus(&bp, call, scb);
		if (ret < 0)
			return ret;

		call->count++;
		if (call->count < call->count2)
			goto more_counts;

		call->count = 0;
		call->unmarshall++;
		afs_extract_to_tmp(call);
		/* Fall through */

		/* Extract the callback count and array in two steps */
	case 3:
		_debug("extract CB count");
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		tmp = ntohl(call->tmp);
		_debug("CB count: %u", tmp);
		if (tmp != call->count2)
			return afs_protocol_error(call, -EBADMSG,
						  afs_eproto_ibulkst_cb_count);
		call->count = 0;
		call->unmarshall++;
	more_cbs:
		afs_extract_to_buf(call, sizeof(struct yfs_xdr_YFSCallBack));
		/* Fall through */

	case 4:
		_debug("extract CB array");
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		_debug("unmarshall CB array");
		bp = call->buffer;
		scb = &call->out_scb[call->count];
		xdr_decode_YFSCallBack(&bp, call, scb);
		call->count++;
		if (call->count < call->count2)
			goto more_cbs;

		afs_extract_to_buf(call, sizeof(struct yfs_xdr_YFSVolSync));
		call->unmarshall++;
		/* Fall through */

	case 5:
		ret = afs_extract_data(call, false);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		xdr_decode_YFSVolSync(&bp, call->out_volsync);

		call->unmarshall++;
		/* Fall through */

	case 6:
		break;
	}

	_leave(" = 0 [done]");
	return 0;
}