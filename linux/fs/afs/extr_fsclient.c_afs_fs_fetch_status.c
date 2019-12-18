#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct afs_volsync {int dummy; } ;
struct afs_status_cb {int dummy; } ;
struct afs_net {int dummy; } ;
struct TYPE_6__ {int error; } ;
struct afs_fs_cursor {TYPE_2__ ac; TYPE_3__* cbi; int /*<<< orphan*/  key; } ;
struct afs_fid {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_call {int /*<<< orphan*/ * request; struct afs_volsync* out_volsync; struct afs_status_cb* out_scb; struct afs_fid* out_fid; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {TYPE_1__* server; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_IS_YFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSFETCHSTATUS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_RXFSFetchStatus ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_make_call (TYPE_2__*,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_set_fc_call (struct afs_call*,struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,TYPE_3__*) ; 
 int afs_wait_for_call_to_complete (struct afs_call*,TYPE_2__*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,struct afs_fid*) ; 
 int yfs_fs_fetch_status (struct afs_fs_cursor*,struct afs_net*,struct afs_fid*,struct afs_status_cb*,struct afs_volsync*) ; 

int afs_fs_fetch_status(struct afs_fs_cursor *fc,
			struct afs_net *net,
			struct afs_fid *fid,
			struct afs_status_cb *scb,
			struct afs_volsync *volsync)
{
	struct afs_call *call;
	__be32 *bp;

	if (test_bit(AFS_SERVER_FL_IS_YFS, &fc->cbi->server->flags))
		return yfs_fs_fetch_status(fc, net, fid, scb, volsync);

	_enter(",%x,{%llx:%llu},,",
	       key_serial(fc->key), fid->vid, fid->vnode);

	call = afs_alloc_flat_call(net, &afs_RXFSFetchStatus, 16, (21 + 3 + 6) * 4);
	if (!call) {
		fc->ac.error = -ENOMEM;
		return -ENOMEM;
	}

	call->key = fc->key;
	call->out_fid = fid;
	call->out_scb = scb;
	call->out_volsync = volsync;

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSFETCHSTATUS);
	bp[1] = htonl(fid->vid);
	bp[2] = htonl(fid->vnode);
	bp[3] = htonl(fid->unique);

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, fid);
	afs_set_fc_call(call, fc);
	afs_make_call(&fc->ac, call, GFP_NOFS);
	return afs_wait_for_call_to_complete(call, &fc->ac);
}