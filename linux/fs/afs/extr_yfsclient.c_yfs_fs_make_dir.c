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
typedef  int /*<<< orphan*/  umode_t ;
struct yfs_xdr_YFSVolSync {int dummy; } ;
struct yfs_xdr_YFSStoreStatus {int dummy; } ;
struct yfs_xdr_YFSFid {int dummy; } ;
struct yfs_xdr_YFSFetchStatus {int dummy; } ;
struct yfs_xdr_YFSCallBack {int dummy; } ;
struct yfs_xdr_RPCFlags {int dummy; } ;
struct afs_vnode {int /*<<< orphan*/  fid; } ;
struct afs_status_cb {int dummy; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_fid {int dummy; } ;
struct afs_call {int /*<<< orphan*/ * request; struct afs_status_cb* out_scb; struct afs_fid* out_fid; struct afs_status_cb* out_dir_scb; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  YFSMAKEDIR ; 
 int /*<<< orphan*/  _enter (char*) ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_set_fc_call (struct afs_call*,struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 int afs_wait_for_call_to_complete (struct afs_call*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call1 (struct afs_call*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * xdr_encode_YFSFid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_YFSStoreStatus_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_string (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * xdr_encode_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xdr_strlen (size_t) ; 
 int /*<<< orphan*/  yfs_RXFSMakeDir ; 
 int /*<<< orphan*/  yfs_check_req (struct afs_call*,int /*<<< orphan*/ *) ; 

int yfs_fs_make_dir(struct afs_fs_cursor *fc,
		    const char *name,
		    umode_t mode,
		    struct afs_status_cb *dvnode_scb,
		    struct afs_fid *newfid,
		    struct afs_status_cb *new_scb)
{
	struct afs_vnode *dvnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(dvnode);
	size_t namesz, reqsz, rplsz;
	__be32 *bp;

	_enter("");

	namesz = strlen(name);
	reqsz = (sizeof(__be32) +
		 sizeof(struct yfs_xdr_RPCFlags) +
		 sizeof(struct yfs_xdr_YFSFid) +
		 xdr_strlen(namesz) +
		 sizeof(struct yfs_xdr_YFSStoreStatus));
	rplsz = (sizeof(struct yfs_xdr_YFSFid) +
		 sizeof(struct yfs_xdr_YFSFetchStatus) +
		 sizeof(struct yfs_xdr_YFSFetchStatus) +
		 sizeof(struct yfs_xdr_YFSCallBack) +
		 sizeof(struct yfs_xdr_YFSVolSync));

	call = afs_alloc_flat_call(net, &yfs_RXFSMakeDir, reqsz, rplsz);
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->out_dir_scb = dvnode_scb;
	call->out_fid = newfid;
	call->out_scb = new_scb;

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSMAKEDIR);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvnode->fid);
	bp = xdr_encode_string(bp, name, namesz);
	bp = xdr_encode_YFSStoreStatus_mode(bp, mode);
	yfs_check_req(call, bp);

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call1(call, &dvnode->fid, name);
	afs_set_fc_call(call, fc);
	afs_make_call(&fc->ac, call, GFP_NOFS);
	return afs_wait_for_call_to_complete(call, &fc->ac);
}