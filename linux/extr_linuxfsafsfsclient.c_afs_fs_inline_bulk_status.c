#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct afs_volsync {int dummy; } ;
struct afs_net {int dummy; } ;
struct TYPE_2__ {int error; } ;
struct afs_fs_cursor {TYPE_1__ ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  cb_break; int /*<<< orphan*/  key; } ;
typedef  struct afs_volsync afs_file_status ;
struct afs_fid {unsigned int vid; unsigned int vnode; unsigned int unique; } ;
typedef  struct afs_volsync afs_callback ;
struct afs_call {unsigned int count2; int /*<<< orphan*/  cb_break; int /*<<< orphan*/ * request; struct afs_volsync** reply; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int FSINLINEBULKSTATUS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  afs_RXFSInlineBulkStatus ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int afs_make_call (TYPE_1__*,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 void* htonl (unsigned int) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,struct afs_fid*) ; 

int afs_fs_inline_bulk_status(struct afs_fs_cursor *fc,
			      struct afs_net *net,
			      struct afs_fid *fids,
			      struct afs_file_status *statuses,
			      struct afs_callback *callbacks,
			      unsigned int nr_fids,
			      struct afs_volsync *volsync)
{
	struct afs_call *call;
	__be32 *bp;
	int i;

	_enter(",%x,{%x:%u},%u",
	       key_serial(fc->key), fids[0].vid, fids[1].vnode, nr_fids);

	call = afs_alloc_flat_call(net, &afs_RXFSInlineBulkStatus,
				   (2 + nr_fids * 3) * 4,
				   21 * 4);
	if (!call) {
		fc->ac.error = -ENOMEM;
		return -ENOMEM;
	}

	call->key = fc->key;
	call->reply[0] = NULL; /* vnode for fid[0] */
	call->reply[1] = statuses;
	call->reply[2] = callbacks;
	call->reply[3] = volsync;
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

	call->cb_break = fc->cb_break;
	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &fids[0]);
	return afs_make_call(&fc->ac, call, GFP_NOFS, false);
}