#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_1__ fid; } ;
struct afs_status_cb {int dummy; } ;
struct afs_net {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct afs_fs_cursor {TYPE_2__ ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_call {int /*<<< orphan*/ * request; int /*<<< orphan*/ * out_volsync; struct afs_status_cb* out_scb; int /*<<< orphan*/ * ret_acl; int /*<<< orphan*/  key; } ;
struct afs_acl {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSFETCHACL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_RXFSFetchACL ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_make_call (TYPE_2__*,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 scalar_t__ afs_wait_for_call_to_complete (struct afs_call*,TYPE_2__*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,TYPE_1__*) ; 

struct afs_acl *afs_fs_fetch_acl(struct afs_fs_cursor *fc,
				 struct afs_status_cb *scb)
{
	struct afs_vnode *vnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(vnode);
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(fc->key), vnode->fid.vid, vnode->fid.vnode);

	call = afs_alloc_flat_call(net, &afs_RXFSFetchACL, 16, (21 + 6) * 4);
	if (!call) {
		fc->ac.error = -ENOMEM;
		return ERR_PTR(-ENOMEM);
	}

	call->key = fc->key;
	call->ret_acl = NULL;
	call->out_scb = scb;
	call->out_volsync = NULL;

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSFETCHACL);
	bp[1] = htonl(vnode->fid.vid);
	bp[2] = htonl(vnode->fid.vnode);
	bp[3] = htonl(vnode->fid.unique);

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &vnode->fid);
	afs_make_call(&fc->ac, call, GFP_KERNEL);
	return (struct afs_acl *)afs_wait_for_call_to_complete(call, &fc->ac);
}