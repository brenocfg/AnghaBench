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
typedef  int u32 ;
struct iattr {int ia_valid; int ia_size; } ;
struct TYPE_4__ {int vid; int vnode; int unique; } ;
struct TYPE_3__ {scalar_t__ data_version; } ;
struct afs_vnode {TYPE_2__ fid; TYPE_1__ status; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_call {int /*<<< orphan*/ * request; scalar_t__ expected_version; struct afs_vnode** reply; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_SIZE ; 
 int ENOMEM ; 
 int FSSTOREDATA64 ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  afs_RXFSStoreData64_as_Status ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,TYPE_2__*) ; 
 int /*<<< orphan*/  xdr_encode_AFS_StoreStatus (int /*<<< orphan*/ **,struct iattr*) ; 

__attribute__((used)) static int afs_fs_setattr_size64(struct afs_fs_cursor *fc, struct iattr *attr)
{
	struct afs_vnode *vnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(vnode);
	__be32 *bp;

	_enter(",%x,{%x:%u},,",
	       key_serial(fc->key), vnode->fid.vid, vnode->fid.vnode);

	ASSERT(attr->ia_valid & ATTR_SIZE);

	call = afs_alloc_flat_call(net, &afs_RXFSStoreData64_as_Status,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->reply[0] = vnode;
	call->expected_version = vnode->status.data_version + 1;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA64);
	*bp++ = htonl(vnode->fid.vid);
	*bp++ = htonl(vnode->fid.vnode);
	*bp++ = htonl(vnode->fid.unique);

	xdr_encode_AFS_StoreStatus(&bp, attr);

	*bp++ = 0;				/* position of start of write */
	*bp++ = 0;
	*bp++ = 0;				/* size of write */
	*bp++ = 0;
	*bp++ = htonl(attr->ia_size >> 32);	/* new file length */
	*bp++ = htonl((u32) attr->ia_size);

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &vnode->fid);
	return afs_make_call(&fc->ac, call, GFP_NOFS, false);
}