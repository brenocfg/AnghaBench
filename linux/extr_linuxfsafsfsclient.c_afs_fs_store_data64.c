#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int vid; int vnode; int unique; } ;
struct TYPE_6__ {int tv_sec; } ;
struct TYPE_7__ {TYPE_2__ i_mtime; } ;
struct TYPE_5__ {scalar_t__ data_version; } ;
struct afs_vnode {TYPE_4__ fid; TYPE_3__ vfs_inode; TYPE_1__ status; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_call {unsigned int first_offset; unsigned int last_to; int send_pages; int /*<<< orphan*/ * request; scalar_t__ expected_version; void* last; void* first; struct afs_vnode** reply; struct address_space* mapping; int /*<<< orphan*/  key; } ;
struct address_space {int dummy; } ;
typedef  void* pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int AFS_SET_MTIME ; 
 int ENOMEM ; 
 int FSSTOREDATA64 ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  afs_RXFSStoreData64 ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,TYPE_4__*) ; 

__attribute__((used)) static int afs_fs_store_data64(struct afs_fs_cursor *fc,
			       struct address_space *mapping,
			       pgoff_t first, pgoff_t last,
			       unsigned offset, unsigned to,
			       loff_t size, loff_t pos, loff_t i_size)
{
	struct afs_vnode *vnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(vnode);
	__be32 *bp;

	_enter(",%x,{%x:%u},,",
	       key_serial(fc->key), vnode->fid.vid, vnode->fid.vnode);

	call = afs_alloc_flat_call(net, &afs_RXFSStoreData64,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->mapping = mapping;
	call->reply[0] = vnode;
	call->first = first;
	call->last = last;
	call->first_offset = offset;
	call->last_to = to;
	call->send_pages = true;
	call->expected_version = vnode->status.data_version + 1;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA64);
	*bp++ = htonl(vnode->fid.vid);
	*bp++ = htonl(vnode->fid.vnode);
	*bp++ = htonl(vnode->fid.unique);

	*bp++ = htonl(AFS_SET_MTIME); /* mask */
	*bp++ = htonl(vnode->vfs_inode.i_mtime.tv_sec); /* mtime */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = 0; /* unix mode */
	*bp++ = 0; /* segment size */

	*bp++ = htonl(pos >> 32);
	*bp++ = htonl((u32) pos);
	*bp++ = htonl(size >> 32);
	*bp++ = htonl((u32) size);
	*bp++ = htonl(i_size >> 32);
	*bp++ = htonl((u32) i_size);

	trace_afs_make_fs_call(call, &vnode->fid);
	return afs_make_call(&fc->ac, call, GFP_NOFS, false);
}