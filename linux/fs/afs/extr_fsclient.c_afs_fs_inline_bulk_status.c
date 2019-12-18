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
struct afs_fid {unsigned int vid; unsigned int vnode; unsigned int unique; } ;
struct afs_call {unsigned int count2; int /*<<< orphan*/ * request; struct afs_volsync* out_volsync; struct afs_status_cb* out_scb; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {TYPE_1__* server; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_IS_YFS ; 
 int ENOMEM ; 
 unsigned int FSINLINEBULKSTATUS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  afs_RXFSInlineBulkStatus ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_make_call (TYPE_2__*,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_set_fc_call (struct afs_call*,struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,TYPE_3__*) ; 
 int afs_wait_for_call_to_complete (struct afs_call*,TYPE_2__*) ; 
 void* htonl (unsigned int) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,struct afs_fid*) ; 
 int yfs_fs_inline_bulk_status (struct afs_fs_cursor*,struct afs_net*,struct afs_fid*,struct afs_status_cb*,unsigned int,struct afs_volsync*) ; 

int afs_fs_inline_bulk_status(struct afs_fs_cursor *fc,
			      struct afs_net *net,
			      struct afs_fid *fids,
			      struct afs_status_cb *statuses,
			      unsigned int nr_fids,
			      struct afs_volsync *volsync)
{
	struct afs_call *call;
	__be32 *bp;
	int i;

	if (test_bit(AFS_SERVER_FL_IS_YFS, &fc->cbi->server->flags))
		return yfs_fs_inline_bulk_status(fc, net, fids, statuses,
						 nr_fids, volsync);

	_enter(",%x,{%llx:%llu},%u",
	       key_serial(fc->key), fids[0].vid, fids[1].vnode, nr_fids);

	call = afs_alloc_flat_call(net, &afs_RXFSInlineBulkStatus,
				   (2 + nr_fids * 3) * 4,
				   21 * 4);
	if (!call) {
		fc->ac.error = -ENOMEM;
		return -ENOMEM;
	}

	call->key = fc->key;
	call->out_scb = statuses;
	call->out_volsync = volsync;
	call->count2 = nr_fids;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSINLINEBULKSTATUS);
	*bp++ = htonl(nr_fids);
	for (i = 0; i < nr_fids; i++) {
		*bp++ = htonl(fids[i].vid);
		*bp++ = htonl(fids[i].vnode);
		*bp++ = htonl(fids[i].unique);
	}

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &fids[0]);
	afs_set_fc_call(call, fc);
	afs_make_call(&fc->ac, call, GFP_NOFS);
	return afs_wait_for_call_to_complete(call, &fc->ac);
}