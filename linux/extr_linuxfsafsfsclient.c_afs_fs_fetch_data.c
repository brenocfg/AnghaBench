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
struct TYPE_4__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_version; } ;
struct afs_vnode {TYPE_2__ fid; int /*<<< orphan*/  usage; scalar_t__ len; scalar_t__ pos; TYPE_1__ status; } ;
struct afs_read {TYPE_2__ fid; int /*<<< orphan*/  usage; scalar_t__ len; scalar_t__ pos; TYPE_1__ status; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  cb_break; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_call {int /*<<< orphan*/  cb_break; int /*<<< orphan*/ * request; int /*<<< orphan*/  expected_version; struct afs_vnode** reply; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FSFETCHDATA ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXFSFetchData ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int afs_fs_fetch_data64 (struct afs_fs_cursor*,struct afs_vnode*) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,TYPE_2__*) ; 
 scalar_t__ upper_32_bits (scalar_t__) ; 

int afs_fs_fetch_data(struct afs_fs_cursor *fc, struct afs_read *req)
{
	struct afs_vnode *vnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(vnode);
	__be32 *bp;

	if (upper_32_bits(req->pos) ||
	    upper_32_bits(req->len) ||
	    upper_32_bits(req->pos + req->len))
		return afs_fs_fetch_data64(fc, req);

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXFSFetchData, 24, (21 + 3 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->reply[0] = vnode;
	call->reply[1] = NULL; /* volsync */
	call->reply[2] = req;
	call->expected_version = vnode->status.data_version;

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSFETCHDATA);
	bp[1] = htonl(vnode->fid.vid);
	bp[2] = htonl(vnode->fid.vnode);
	bp[3] = htonl(vnode->fid.unique);
	bp[4] = htonl(lower_32_bits(req->pos));
	bp[5] = htonl(lower_32_bits(req->len));

	refcount_inc(&req->usage);
	call->cb_break = fc->cb_break;
	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &vnode->fid);
	return afs_make_call(&fc->ac, call, GFP_NOFS, false);
}