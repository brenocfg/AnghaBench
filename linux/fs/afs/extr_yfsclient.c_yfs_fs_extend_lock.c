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
struct yfs_xdr_YFSVolSync {int dummy; } ;
struct yfs_xdr_YFSFid {int dummy; } ;
struct yfs_xdr_YFSFetchStatus {int dummy; } ;
struct afs_vnode {int /*<<< orphan*/  fid; } ;
struct afs_status_cb {int dummy; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_call {int /*<<< orphan*/ * request; struct afs_status_cb* out_scb; struct afs_vnode* lvnode; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  YFSEXTENDLOCK ; 
 int /*<<< orphan*/  _enter (char*) ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_set_fc_call (struct afs_call*,struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 int afs_wait_for_call_to_complete (struct afs_call*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_YFSFid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yfs_RXYFSExtendLock ; 
 int /*<<< orphan*/  yfs_check_req (struct afs_call*,int /*<<< orphan*/ *) ; 

int yfs_fs_extend_lock(struct afs_fs_cursor *fc, struct afs_status_cb *scb)
{
	struct afs_vnode *vnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(vnode);
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &yfs_RXYFSExtendLock,
				   sizeof(__be32) * 2 +
				   sizeof(struct yfs_xdr_YFSFid),
				   sizeof(struct yfs_xdr_YFSFetchStatus) +
				   sizeof(struct yfs_xdr_YFSVolSync));
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->lvnode = vnode;
	call->out_scb = scb;

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSEXTENDLOCK);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vnode->fid);
	yfs_check_req(call, bp);

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &vnode->fid);
	afs_set_fc_call(call, fc);
	afs_make_call(&fc->ac, call, GFP_NOFS);
	return afs_wait_for_call_to_complete(call, &fc->ac);
}