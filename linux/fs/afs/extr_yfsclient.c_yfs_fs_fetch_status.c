#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct yfs_xdr_YFSVolSync {int dummy; } ;
struct yfs_xdr_YFSFid {int dummy; } ;
struct yfs_xdr_YFSFetchStatus {int dummy; } ;
struct yfs_xdr_YFSCallBack {int dummy; } ;
struct afs_volsync {int dummy; } ;
struct afs_status_cb {int dummy; } ;
struct afs_net {int dummy; } ;
struct TYPE_3__ {int error; } ;
struct afs_fs_cursor {TYPE_1__ ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  key; } ;
struct afs_fid {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_call {int /*<<< orphan*/ * request; struct afs_volsync* out_volsync; struct afs_status_cb* out_scb; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  YFSFETCHSTATUS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_make_call (TYPE_1__*,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_set_fc_call (struct afs_call*,struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 int afs_wait_for_call_to_complete (struct afs_call*,TYPE_1__*) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,struct afs_fid*) ; 
 int /*<<< orphan*/ * xdr_encode_YFSFid (int /*<<< orphan*/ *,struct afs_fid*) ; 
 int /*<<< orphan*/ * xdr_encode_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yfs_RXYFSFetchStatus ; 
 int /*<<< orphan*/  yfs_check_req (struct afs_call*,int /*<<< orphan*/ *) ; 

int yfs_fs_fetch_status(struct afs_fs_cursor *fc,
			struct afs_net *net,
			struct afs_fid *fid,
			struct afs_status_cb *scb,
			struct afs_volsync *volsync)
{
	struct afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(fc->key), fid->vid, fid->vnode);

	call = afs_alloc_flat_call(net, &yfs_RXYFSFetchStatus,
				   sizeof(__be32) * 2 +
				   sizeof(struct yfs_xdr_YFSFid),
				   sizeof(struct yfs_xdr_YFSFetchStatus) +
				   sizeof(struct yfs_xdr_YFSCallBack) +
				   sizeof(struct yfs_xdr_YFSVolSync));
	if (!call) {
		fc->ac.error = -ENOMEM;
		return -ENOMEM;
	}

	call->key = fc->key;
	call->out_scb = scb;
	call->out_volsync = volsync;

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSFETCHSTATUS);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, fid);
	yfs_check_req(call, bp);

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, fid);
	afs_set_fc_call(call, fc);
	afs_make_call(&fc->ac, call, GFP_NOFS);
	return afs_wait_for_call_to_complete(call, &fc->ac);
}